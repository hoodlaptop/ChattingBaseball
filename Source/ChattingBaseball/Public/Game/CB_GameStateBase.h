// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CB_GameStateBase.generated.h"


class ACB_PlayerState;

UCLASS()
class CHATTINGBASEBALL_API ACB_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString);
	
	UFUNCTION(BlueprintPure, Category = "Turn")
	int32 GetRemainingTurnTime() const { return RemainingTurnTime; }

	UFUNCTION(BlueprintPure, Category = "Turn")
	ACB_PlayerState* GetCurrentTurnPlayerState() const { return CurrentTurnPlayerState; }
	
	UPROPERTY(Replicated)
	int32 RemainingTurnTime = 0;

	UPROPERTY(Replicated)
	TObjectPtr<ACB_PlayerState> CurrentTurnPlayerState = nullptr;
};

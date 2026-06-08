// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CB_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGBASEBALL_API ACB_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACB_PlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();

	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;
};

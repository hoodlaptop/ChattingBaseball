// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CB_PlayerController.generated.h"

class UCB_ChatInput;
class UUserWidget;


UCLASS()
class CHATTINGBASEBALL_API ACB_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACB_PlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void SetChatMessageString(const FString& InChatMessageString);
	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	UPROPERTY(EditAnywhere, Category="Debug")
	bool bIsDebug = false;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCB_ChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UCB_ChatInput> ChatInputWidgetInstance;

	UPROPERTY()
	FString ChatMessageString;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;
};

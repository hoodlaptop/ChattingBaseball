// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball


#include "Player/CB_PlayerController.h"

#include "EngineUtils.h"
#include "ChattingBaseball/ChattingBaseball.h"
#include "Game/CB_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/CB_PlayerState.h"
#include "UI/CB_ChatInput.h"

ACB_PlayerController::ACB_PlayerController()
{
	bReplicates = true;
}

void ACB_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false) return;

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass))
	{
		ChatInputWidgetInstance = CreateWidget<UCB_ChatInput>(this, ChatInputWidgetClass);

		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass))
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);

		if (IsValid(NotificationTextWidgetInstance))
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ACB_PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ACB_PlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController())
	{
		// 접두사(이름/시도 횟수)는 서버에서 시도 횟수 증가 후 생성한다. 여기서는 원본 입력만 전송.
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ACB_PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	if (bIsDebug)
	{
		FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
		FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
		ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);
		return;
	}

	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ACB_PlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ACB_PlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM))
	{
		ACB_GameModeBase* CBGM = Cast<ACB_GameModeBase>(GM);
		if (IsValid(CBGM))
		{
			CBGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

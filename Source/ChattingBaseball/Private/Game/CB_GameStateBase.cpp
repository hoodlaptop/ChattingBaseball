// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball


#include "Game/CB_GameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/CB_PlayerController.h"

void ACB_GameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, RemainingTurnTime);
	DOREPLIFETIME(ThisClass, CurrentTurnPlayerState);
}

void ACB_GameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (IsValid(PC))
		{
			ACB_PlayerController* CBPC = Cast<ACB_PlayerController>(PC);
			if (IsValid(CBPC))
			{
				FString NotificationString = InNameString + TEXT(" has joined the game");
				CBPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}



// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball


#include "Player/CB_PlayerState.h"

#include "Net/UnrealNetwork.h"

ACB_PlayerState::ACB_PlayerState()
	: PlayerNameString(TEXT("None"))
	  , CurrentGuessCount(0)
	  , MaxGuessCount(3)
{
	bReplicates = true;
}

void ACB_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerNameString);
	DOREPLIFETIME(ThisClass, CurrentGuessCount);
	DOREPLIFETIME(ThisClass, MaxGuessCount);
}

FString ACB_PlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGuessCount) + TEXT("/") +
		FString::FromInt(MaxGuessCount) + TEXT(")");
	return PlayerInfoString;
}

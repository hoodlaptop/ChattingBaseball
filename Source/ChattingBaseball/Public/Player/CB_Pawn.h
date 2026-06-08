// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CB_Pawn.generated.h"

UCLASS()
class CHATTINGBASEBALL_API ACB_Pawn : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
};

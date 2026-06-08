// Copyright 2026 이길호. All Rights Reserved.Project: ChattingBaseball


#include "UI/CB_ChatInput.h"

#include "Components/EditableTextBox.h"
#include "Player/CB_PlayerController.h"

void UCB_ChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(EditableTextBox_ChatInput))
	{
		if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) ==
			false)
		{
			EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
		}
	}
}

void UCB_ChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(EditableTextBox_ChatInput))
	{
		if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) ==
			true)
		{
			EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
		}
	}
}

void UCB_ChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();

		if (IsValid(OwningPlayerController))
		{
			ACB_PlayerController* OwningCBPlayerController = Cast<ACB_PlayerController>(OwningPlayerController);
			if (IsValid(OwningCBPlayerController))
			{
				OwningCBPlayerController->SetChatMessageString(Text.ToString());

				EditableTextBox_ChatInput->SetText(FText());
			}
		}
	}
}

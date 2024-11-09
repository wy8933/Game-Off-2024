// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/RichTextBlock.h"

void UDialogueWidget::SetDialogueText(const FText& NewText)
{
	if (DialogueTextBlock)
	{
		// Set the text in the RichTextBlock
		DialogueTextBlock->SetText(NewText);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionPromptWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "InteractPrompt"


void UInteractionPromptWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetPromptText();
}


void UInteractionPromptWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//SetPromptText();
}

void UInteractionPromptWidget::SetPromptText()
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("InteractType"), InteractionType);
	FText prompt = FText::Format(LOCTEXT("InteractPrompt", "Press 'E' to {InteractType}"), Args);
	InteractText->SetText(prompt);
}
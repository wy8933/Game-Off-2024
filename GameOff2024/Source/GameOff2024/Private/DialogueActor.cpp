// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueActor.h"
#include "Blueprint/UserWidget.h"
ADialogueActor::ADialogueActor()
{
    // Set a default dialogue text
    DialogueText = FText::FromString("default text");
}

void ADialogueActor::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the widget class is set before creating the widget
    if (DialogueWidgetClass)
    {
        DialogueWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidgetInstance)
        {
            // Initially hide the widget
            DialogueWidgetInstance->AddToViewport();
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void ADialogueActor::Interact()
{
    Super::Interact();

    if (DialogueWidgetInstance)
    {
        // Show the dialogue widget when interacted with
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Visible);
    }
}
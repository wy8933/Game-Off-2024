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
   
    DialogueWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), DialogueWidgetClass);
    if (DialogueWidgetInstance)
    {
        // Initially hide the widget
        DialogueWidgetInstance->AddToViewport();
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    }
    
}

void ADialogueActor::Interact()
{
    Super::Interact();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor interacted"));
    }
    if (DialogueWidgetInstance)
    {
        // Show the dialogue widget when interacted with it
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Widget created"));
        }
    }
}
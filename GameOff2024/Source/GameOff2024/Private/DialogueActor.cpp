// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueActor.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

ADialogueActor::ADialogueActor()
{
    // Set a default dialogue text
    DialogueText = FText::FromString("default text");
    DialogueSystemManager = CreateDefaultSubobject<UDialogueSystemManager>(TEXT("DialogueSystemManager"));
}

void ADialogueActor::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the widget class is set before creating the widget
    if (DialogueWidgetClass)
    {
        DialogueWidgetInstance = CreateWidget<UDialogue>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidgetInstance)
        {
            // Initially hide the widget
            DialogueWidgetInstance->AddToViewport();
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    // Initialize Dialogue System Manager with starting dialogue
    if (DialogueSystemManager)
    {
        DialogueSystemManager->CurrentNodeID = 0;
    }
    
}


void ADialogueActor::Interact()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor interacted"));
    }

    if (DialogueSystemManager && DialogueWidgetInstance)
    {
        // Cast DialogueWidgetInstance to UDialogue to access UpdateDialogue
        if (DialogueWidgetInstance)
        {
            FDialogueNode CurrentNode = DialogueSystemManager->GetCurrentDialogueNode();

            // Display the current node's text in the dialogue widget
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            DialogueWidgetInstance->UpdateDialogue(CurrentNode.SpeakerName, CurrentNode.DialogueText);

            // Move to the next node
            DialogueSystemManager->ProgressToNextNode();
        }
    }
}
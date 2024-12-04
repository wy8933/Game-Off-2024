#include "DialogueSystemManager.h"
#include "Dialogue.h"
#include "Components/AudioComponent.h"
#include "Blueprint/UserWidget.h"

ADialogueSystemManager::ADialogueSystemManager()
{
    CurrentNodeID = 0;
    DialogueDataTable = nullptr;
    DialogueWidgetInstance = nullptr;

    // Create the audio component
    DialogueAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DialogueAudioComponent"));
    DialogueAudioComponent->bAutoActivate = false;
    DialogueAudioComponent->OnAudioFinished.AddDynamic(this, &ADialogueSystemManager::OnDialogueAudioFinished);
}

void ADialogueSystemManager::StartDialogue(UDataTable* NewDialogueTable, int32 StartingNodeID)
{
    DialogueDataTable = NewDialogueTable;
    CurrentNodeID = StartingNodeID;

    if (DialogueDataTable && DialogueWidgetInstance)
    {
        // Make the widget visible and display the first node
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        DisplayCurrentNode();
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DialogueDataTable or DialogueWidgetInstance is null!"));
        }
    }
}

FDialogueNode ADialogueSystemManager::GetCurrentDialogueNode()
{
    if (!DialogueDataTable)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DialogueDataTable is null!"));
        }
        return FDialogueNode();
    }

    // Get the current node by ID
    FName RowName = FName(*FString::FromInt(CurrentNodeID));
    FDialogueNode* Node = DialogueDataTable->FindRow<FDialogueNode>(RowName, TEXT("Lookup Dialogue Node"));

    if (Node)
    {
        return *Node;
    }
    else
    {
        if (GEngine)
        {
            FString ErrorMessage = FString::Printf(TEXT("Dialogue node with ID %d not found"), CurrentNodeID);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *ErrorMessage);
        }
        return FDialogueNode();
    }
}

void ADialogueSystemManager::DisplayCurrentNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();

    // Update the dialogue widget
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->UpdateDialogue(CurrentNode.SpeakerName, CurrentNode.DialogueText);
    }

    // Play the audio for the current node
    if (CurrentNode.DialogueAudio && DialogueAudioComponent)
    {
        DialogueAudioComponent->SetSound(CurrentNode.DialogueAudio);
        DialogueAudioComponent->Play();
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("No audio found for the current node!"));
        }
        OnDialogueAudioFinished();
    }
}

void ADialogueSystemManager::ProgressToNextNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();

    // Update the node ID to the next one
    CurrentNodeID = CurrentNode.NextNodeID;

    if (CurrentNodeID == -1)
    {
        EndDialogue();
    }
    else
    {
        DisplayCurrentNode();
    }
}

void ADialogueSystemManager::EndDialogue()
{
    // Hide the dialogue widget and reset state
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    }
    CurrentNodeID = 0;
    DialogueDataTable = nullptr;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Dialogue ended!"));
    }
}

void ADialogueSystemManager::OnDialogueAudioFinished()
{
    ProgressToNextNode();
}

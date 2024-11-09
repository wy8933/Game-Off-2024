#include "DialogueActor.h"
#include "Dialogue.h"  // Ensure UDialogue is included
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"

ADialogueActor::ADialogueActor()
{
    // Set default values
    DialogueDataTable = nullptr;
    CurrentNodeID = 0;
    DialogueWidgetInstance = nullptr;
    bIsDialogueActive = false;
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
            DialogueWidgetInstance->AddToViewport();
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    // Load data table if not set
    if (!DialogueDataTable)
    {
        DialogueDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_DialogueTreeData.DT_DialogueTreeData"));
    }

    if (DialogueDataTable == nullptr && GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dialogue DataTable is not set or failed to load!"));
    }
}

void ADialogueActor::Interact()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor interacted"));
    }

    if (DialogueDataTable && DialogueWidgetInstance)
    {
        UDialogue* DialogueWidget = Cast<UDialogue>(DialogueWidgetInstance);
        if (DialogueWidget)
        {
            bIsDialogueActive = true;
            FDialogueNode CurrentNode = GetCurrentDialogueNode();

            // Display the current node's text in the dialogue widget
            DialogueWidget->SetVisibility(ESlateVisibility::Visible);
            DialogueWidget->UpdateDialogue(CurrentNode.SpeakerName, CurrentNode.DialogueText);

            // Move to the next node
            ProgressToNextNode();
        }
    }
}

FDialogueNode ADialogueActor::GetCurrentDialogueNode()
{
    if (!DialogueDataTable)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Data table found"));
        }
        return FDialogueNode();
    }

    // Find the node with the correctID
    FName RowName = FName(*FString::FromInt(CurrentNodeID));
    FDialogueNode* Node = DialogueDataTable->FindRow<FDialogueNode>(RowName, TEXT("Lookup Dialogue Node"));

    // Return the node found or print debug message
    if (Node)
    {
        return *Node;
    }
    else
    {
        if (GEngine)
        {
            FString ErrorMessage = FString::Printf(TEXT("Node with ID %d not found in DialogueDataTable"), CurrentNodeID);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *ErrorMessage);
        }
        return FDialogueNode();
    }
}

void ADialogueActor::ProgressToNextNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();
    if (CurrentNodeID != -1)
    {
        CurrentNodeID = CurrentNode.NextNodeID;
    }
    else
    {
        if (DialogueWidgetInstance)
        {
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            bIsDialogueActive = false;
        }
    }
}

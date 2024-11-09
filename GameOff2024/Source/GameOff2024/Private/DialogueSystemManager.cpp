#include "DialogueSystemManager.h"
#include "Engine/DataTable.h"

FDialogueNode UDialogueSystemManager::GetCurrentDialogueNode()
{
    if (!DialogueDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueDataTable is not set!"));
        return FDialogueNode();
    }

    FDialogueNode* Node = DialogueDataTable->FindRow<FDialogueNode>(FName(*FString::FromInt(CurrentNodeID)), TEXT("Lookup Dialogue Node"));

    return Node ? *Node : FDialogueNode();
}

void UDialogueSystemManager::ProgressToNextNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();

    CurrentNodeID = CurrentNode.NextNodeID;
}

void UDialogueSystemManager::ChooseOption(const FText& ChoiceText)
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();

    FString ChoiceKey = ChoiceText.ToString();

    if (CurrentNode.Choices.Contains(ChoiceKey))
    {
        CurrentNodeID = CurrentNode.Choices[ChoiceKey];
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Choice not found: %s"), *ChoiceKey);
    }
}

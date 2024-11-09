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
    if (CurrentNode.NextNodeID != -1)
    {
        CurrentNodeID = CurrentNode.NextNodeID;
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("End of dialogue"));
    }
}

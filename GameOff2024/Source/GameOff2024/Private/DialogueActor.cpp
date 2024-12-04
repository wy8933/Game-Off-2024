#include "DialogueActor.h"
#include "DialogueSystemManager.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"

ADialogueActor::ADialogueActor()
{
    
}

void ADialogueActor::BeginPlay()
{
    Super::BeginPlay();

    if (!DialogueSystemManager)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DialogueSystemManager is not set in the DialogueActor!"));
        }
    }
}

void ADialogueActor::Interact(AGameOff2024Character* Interactor)
{
    if (!DialogueSystemManager)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DialogueSystemManager is null."));
        }
        return;
    }

    if (DialogueDataTable)
    {
        DialogueSystemManager->StartDialogue(DialogueDataTable, StartingNodeID);
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DialogueDataTable is null!"));
        }
    }
}

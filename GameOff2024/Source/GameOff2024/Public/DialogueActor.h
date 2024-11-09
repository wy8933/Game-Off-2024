#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
#include "Engine/DataTable.h"
#include "DialogueNode.h"
#include "Dialogue.h"
#include "DialogueActor.generated.h"

UCLASS()
class GAMEOFF2024_API ADialogueActor : public AInteractableActor
{
    GENERATED_BODY()

public:
    ADialogueActor();

    // Called when the actor is interacted with
    virtual void Interact() override;

protected:
    virtual void BeginPlay() override;

    // Dialogue data table reference
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueDataTable;

    // Current node ID in the dialogue tree
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    int32 CurrentNodeID;

    // The class of the dialogue widget to display
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TSubclassOf<UDialogue> DialogueWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    bool bIsDialogueActive;
    void OnProgressDialogue();
private:
    // The instance of the dialogue widget
    UDialogue* DialogueWidgetInstance;

    // Helper functions for dialogue progression
    FDialogueNode GetCurrentDialogueNode();
    void ProgressToNextNode();
};

#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
#include "Dialogue.h" 
#include "DialogueSystemManager.h"
#include "DialogueNode.h"
#include "DialogueActor.generated.h"

/**
 *
 */
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

    // Dialogue text to display
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FText DialogueText;

    // The class of the dialogue widget to display
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TSubclassOf<UDialogue> DialogueWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDialogueSystemManager* DialogueSystemManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueDataTable;

private:
    // The instance of the dialogue widget
    UDialogue* DialogueWidgetInstance;
};

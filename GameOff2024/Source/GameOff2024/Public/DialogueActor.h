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
    virtual void Interact(AGameOff2024Character* interactor) override;

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
    TSubclassOf<UUserWidget> DialogueWidgetClass;

    // Audio component to play dialogue audio
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue")
    UAudioComponent* DialogueAudioComponent;

    // Indicate if dialogue is active
    UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
    bool bIsDialogueActive;

private:
    // The instance of the dialogue widget
    UDialogue* DialogueWidgetInstance;

    // Helper functions for dialogue progression
    FDialogueNode GetCurrentDialogueNode();
    void StartDialogue();
    void DisplayCurrentNode();
    void ProgressToNextNode();
    void EndDialogue();

    // Callback for when dialogue audio finishes
    UFUNCTION()
    void OnDialogueAudioFinished();
};
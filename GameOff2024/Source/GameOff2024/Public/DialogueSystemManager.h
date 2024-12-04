#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.h"
#include "Components/AudioComponent.h"
#include "DialogueSystemManager.generated.h"

UCLASS(Blueprintable)
class GAMEOFF2024_API ADialogueSystemManager : public AActor
{
    GENERATED_BODY()

public:
    ADialogueSystemManager();

    // Current dialogue node ID
    UPROPERTY(BlueprintReadWrite, Category = "Dialogue")
    int32 CurrentNodeID;

    // Data table containing the dialogue
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueDataTable;

    // Dialogue widget
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    class UDialogue* DialogueWidgetInstance;

    // Audio component for playing dialogue audio
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogue")
    class UAudioComponent* DialogueAudioComponent;

    // Starts the dialogue from the node ID
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void StartDialogue(UDataTable* NewDialogueTable, int32 StartingNodeID);

    // Gets the current dialogue node
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    FDialogueNode GetCurrentDialogueNode();

    // Progress to the next node
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ProgressToNextNode();

    // Ends the dialogue
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void EndDialogue();

private:
    // Handles displaying the current dialogue node
    void DisplayCurrentNode();

    // Callback for when dialogue audio finishes playing
    UFUNCTION()
    void OnDialogueAudioFinished();
};

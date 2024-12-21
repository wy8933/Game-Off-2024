#pragma once

#include "CoreMinimal.h"
#include "DialogueSystemManager.h"
#include "../InteractableActor.h"
#include "DialogueActor.generated.h"

UCLASS()
class GAMEOFF2024_API ADialogueActor : public AInteractableActor
{
    GENERATED_BODY()

public:
    ADialogueActor();

    // Called when the actor is interacted with
    virtual void Interact(AGameOff2024Character* Interactor) override; 

protected:
    virtual void BeginPlay() override;

    // Dialogue System Manager
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
    ADialogueSystemManager* DialogueSystemManager;
     
    //DataTable containing dialogue nodes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueDataTable;

    // The ID of the starting dialogue node
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    int32 StartingNodeID = 0;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void StartDialogue();
};

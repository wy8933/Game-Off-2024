// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
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
    TSubclassOf<UUserWidget> DialogueWidgetClass;

private:
    // The instance of the dialogue widget
    UUserWidget* DialogueWidgetInstance;
};
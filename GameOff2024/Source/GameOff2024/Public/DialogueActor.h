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
	// Sets default values for this actor's properties
	ADialogueActor();
	virtual void Tick(float DeltaTime) override;
};

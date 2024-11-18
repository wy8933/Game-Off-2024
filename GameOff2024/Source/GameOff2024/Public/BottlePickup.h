// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
#include "BottlePickup.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API ABottlePickup : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	virtual void Interact(AGameOff2024Character* Interactor) override;

};

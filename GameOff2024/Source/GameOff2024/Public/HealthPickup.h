// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API AHealthPickup : public AInteractableActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int HealthRestoreAmount = 50;


	virtual void Interact(AGameOff2024Character* interactor) override;
};

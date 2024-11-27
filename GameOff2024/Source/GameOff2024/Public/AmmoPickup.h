// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../InteractableActor.h"
#include "AmmoPickup.generated.h"

UCLASS()
class GAMEOFF2024_API AAmmoPickup : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int AmmoAmount = 1;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AGameOff2024Character* Interactor) override;

};

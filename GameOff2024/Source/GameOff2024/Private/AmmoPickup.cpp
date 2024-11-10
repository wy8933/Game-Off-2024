// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "Inventory.h"


// Sets default values
AAmmoPickup::AAmmoPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoPickup::Interact(AGameOff2024Character* interactor)
{
	UInventory* inventory = interactor->Inventory;
	AmmoAmount = inventory->TryAddAmmo(AmmoAmount);

	if (AmmoAmount <= 0)
	{
		Destroy();
	}
}


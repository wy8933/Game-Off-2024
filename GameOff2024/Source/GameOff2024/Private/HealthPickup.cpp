// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "../GameOff2024Character.h"

void AHealthPickup::Interact(AGameOff2024Character* Interactor)
{
	bool canRestore = false;

	//canRestore = Interactor -> TryRestoreHealth(HealthRestoreAmount);

	UInventory* inventory = Interactor->Inventory;

	if (inventory->TryAddHealthItem())
	{
		Destroy();
	}
}
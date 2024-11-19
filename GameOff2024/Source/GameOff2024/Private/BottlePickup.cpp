// Fill out your copyright notice in the Description page of Project Settings.


#include "BottlePickup.h"

void ABottlePickup::Interact(AGameOff2024Character* Interactor)
{
	UInventory* inventory = Interactor->Inventory;

	if (inventory->TryAddBottleItem())
	{
		Destroy();
	}
}
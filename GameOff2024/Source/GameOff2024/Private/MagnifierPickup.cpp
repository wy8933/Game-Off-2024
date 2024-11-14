// Fill out your copyright notice in the Description page of Project Settings.


#include "MagnifierPickup.h"

void AMagnifierPickup::Interact(AGameOff2024Character* Interactor)
{
	UInventory* inventory = Interactor->Inventory;
	inventory->HasMagnifier = true;

	Destroy();
}
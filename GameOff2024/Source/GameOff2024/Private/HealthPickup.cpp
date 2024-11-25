// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "../GameOff2024Character.h"

void AHealthPickup::Interact(AGameOff2024Character* Interactor)
{
    //bool canRestore = false;
    // Call the parent class's Interact to trigger InteractBP
    Super::Interact(Interactor);

    // Custom logic for the health pickup
    UInventory* inventory = Interactor->Inventory;
    if (inventory->TryAddHealthItem())
    {
        Destroy();
    }
}
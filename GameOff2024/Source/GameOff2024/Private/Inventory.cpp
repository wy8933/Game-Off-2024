// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"



int UInventory::TryAddAmmo(int amount)
{

	if (CurrentAmmo >= MaxAmmo)
	{
		return amount;
	}
	else
	{
		int leftoverAmmo = 0;

		CurrentAmmo += amount;

		if (CurrentAmmo > MaxAmmo)
		{
			leftoverAmmo = CurrentAmmo - MaxAmmo;
			CurrentAmmo = MaxAmmo;
		}

		OnAmmoChanged.Broadcast(CurrentAmmo, AmmoClipSize, AmmoInClip);

		return leftoverAmmo;
	}
}

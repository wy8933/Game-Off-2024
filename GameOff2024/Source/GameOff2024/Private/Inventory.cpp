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

bool UInventory::TryAddHealthItem()
{
	if (HealthItemsCarried >= MaxHealthItems)
	{
		return false;
	}

	HealthItemsCarried += 1;

	OnHealthItemsChanged.Broadcast(HealthItemsCarried);

	return true;
}

bool UInventory::TryRemoveHealthItem()
{
	if (HealthItemsCarried > 0)
	{
		HealthItemsCarried -= 1;
		
		OnHealthItemsChanged.Broadcast(HealthItemsCarried);

		return true;
	}
	else
	{
		return false;
	}
}

bool UInventory::TryAddBottleItem()
{
	if (BottlesCarried >= MaxBottles)
	{
		return false;
	}

	BottlesCarried += 1;

	OnBottlesCarriedChanged.Broadcast(BottlesCarried);

	return true;
}

bool UInventory::TryReloadWeapon()
{
	if (CurrentAmmo <= AmmoInClip)
	{
		return false;
	}
	
	if (CurrentAmmo < AmmoClipSize)
	{
		AmmoInClip = CurrentAmmo;
	}
	else
	{
		AmmoInClip = AmmoClipSize;
	}

	OnAmmoChanged.Broadcast(CurrentAmmo, AmmoClipSize, AmmoInClip);

	return true;
}

bool UInventory::TryUseWeapon()
{
	if (AmmoInClip <= 0)
	{
		return false;
	}

	AmmoInClip -= 1;

	OnAmmoChanged.Broadcast(CurrentAmmo, AmmoClipSize, AmmoInClip);

	return true;
}

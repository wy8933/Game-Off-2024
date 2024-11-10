// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAmmoChanged, int, CurrentAmmo, int, ClipSize, int, AmmoInClip);

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UInventory : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int CurrentAmmo = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int AmmoClipSize = 6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int MaxAmmo = 18;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int AmmoInClip = 0;

	int TryAddAmmo(int amount);

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;

};

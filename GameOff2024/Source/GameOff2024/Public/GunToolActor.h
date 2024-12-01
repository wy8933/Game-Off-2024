// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolActor.h"
#include "Camera/CameraComponent.h"
#include "Inventory.h"
#include "GunToolActor.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponReloaded);

UCLASS()
class GAMEOFF2024_API AGunToolActor : public AToolActor
{
	GENERATED_BODY()
	
private:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;



public:
	virtual void UseTool() override;
	virtual void Reload();

	UFUNCTION(BlueprintImplementableEvent)
		void ShootGun();

	UFUNCTION(BlueprintImplementableEvent)
		void ReloadGun();

	UPROPERTY();
	UInventory* Inventory;

	UPROPERTY(BlueprintAssignable)
	FOnWeaponFired OnWeaponFired;
	UPROPERTY(BlueprintAssignable)
	FOnWeaponReloaded OnWeaponReloaded;

};

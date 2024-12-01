// Fill out your copyright notice in the Description page of Project Settings.

#include "GunToolActor.h"
#include "HitboxComponent.h"

void AGunToolActor::UseTool()
{
	if (!Inventory)
	{
		return;
	}

	if (Inventory->TryUseWeapon() == false)
	{
		return;
	}


	FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	UHitboxComponent* Hitbox = nullptr;


	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	//RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,		//result
		CameraLocation,	//start
		CameraLocation + (CameraRotation.Vector() * INT16_MAX), //end
		ECC_Visibility, //collision channel
		RV_TraceParams
	);

	if (RV_Hit.bBlockingHit)//did hit something? (bool)
	{
		AActor* actor = RV_Hit.GetActor(); //the hit actor if there is one

		//UE_LOG(LogTemp, Display, TEXT("Hit"));

		if (actor->GetComponentByClass(UHitboxComponent::StaticClass()))
		{
			Hitbox = (UHitboxComponent*)actor;

			Hitbox->TakeDamage(RV_Hit.ImpactPoint);
		}
	}

	if (OnWeaponFired.IsBound())
	{
		OnWeaponFired.Broadcast();
	}
	ShootGun();
}

void AGunToolActor::Reload()
{
	if (!Inventory)
	{
		return;
	}

	if (Inventory->TryReloadWeapon())
	{
		if (OnWeaponReloaded.IsBound())
		{
			OnWeaponReloaded.Broadcast();
		}
	}

	ReloadGun();
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AmmoHUDWidget.h"
#include "HealthHUDWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UAmmoHUDWidget* AmmoHUD;

	UPROPERTY(BlueprintReadWrite)
	UHealthHUDWidget* HealthHUD;

protected:
	virtual void BeginPlay() override;

};

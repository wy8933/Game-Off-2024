// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.h"
#include "AmmoHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UAmmoHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHUD(int CurrentAmmo, int ClipSize, int AmmoInClip);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoClipDisplayText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ExtraAmmoDisplayText;
};

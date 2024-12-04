// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoHUDWidget.h"
#include "Components/TextBlock.h"
#include "Inventory.h"

#define LOCTEXT_NAMESPACE "AmmoDisplay"

void UAmmoHUDWidget::NativeConstruct()
{
	//UInventory::OnAmmoChanged.Add(this*, &UAmmoHUDWidget::UpdateHUD);
	//Inventory.OnAmmoChanged.AddDynamic(Inventory, &UAmmoHUDWidget::UpdateHUD);
}

void UAmmoHUDWidget::UpdateHUD(int CurrentAmmo, int ClipSize, int AmmoInClip)
{
	int ExtraAmmo = CurrentAmmo - AmmoInClip;

	FFormatNamedArguments Args;
	Args.Add(TEXT("AmmoInClip"), AmmoInClip);
	Args.Add(TEXT("ClipSize"), ClipSize);
	Args.Add(TEXT("ExtraAmmo"), ExtraAmmo);

	//FText AmmoClipText = FText::Format(LOCTEXT("AmmoDisplay", "{AmmoInClip}/{ClipSize}"), Args);
	FText AmmoClipText = FText::Format(LOCTEXT("AmmoDisplay", "{AmmoInClip}"), Args);
	AmmoClipDisplayText->SetText(AmmoClipText);

	FText ExtraAmmoText = FText::Format(LOCTEXT("AmmoDisplay", "/{ExtraAmmo}"), Args);
	ExtraAmmoDisplayText->SetText(ExtraAmmoText);
}
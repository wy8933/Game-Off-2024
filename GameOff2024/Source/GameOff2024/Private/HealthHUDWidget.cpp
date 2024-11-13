// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthHUDWidget::UpdateHUDHealthBar(int CurrentHealth, int MaxHealth)
{
	HealthBar->Percent = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
}

void UHealthHUDWidget::UpdateHUDHealthItemsCarried(int CurrentHealthItemsCarried)
{
	HealthItemsCarriedText->SetText(FText::FromString(FString::FromInt(CurrentHealthItemsCarried)));
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthHUDWidget.h"
#include "Components/ProgressBar.h"

void UHealthHUDWidget::UpdateHUD(int CurrentHealth, int MaxHealth)
{
	HealthBar->Percent = static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "BottlesHUDWidget.h"
#include "Components/TextBlock.h"

void UBottlesHUDWidget::UpdateHUD(int BottlesCarried)
{
	BottlesCarriedText->SetText(FText::FromString(FString::FromInt(BottlesCarried)));
}
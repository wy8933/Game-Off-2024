// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UHealthHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void UpdateHUD(int CurrentHealth, int MaxHealth);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};

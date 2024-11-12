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
	void UpdateHUDHealthBar(int CurrentHealth, int MaxHealth);
	UFUNCTION()
	void UpdateHUDHealthItemsCarried(int CurrentHealthItemsCarried);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthItemsCarriedText;
};

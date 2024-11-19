// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BottlesHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UBottlesHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BottlesCarriedText;

public:

	UFUNCTION()
	void UpdateHUD(int BottlesCarried);
};

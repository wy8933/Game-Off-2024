// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionPromptWidget.generated.h"


UCLASS(BlueprintType)
class GAMEOFF2024_API UInteractionPromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	virtual void SetPromptText();

	FText InteractionType = FText::FromString("Interact");

private:
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractText;

};

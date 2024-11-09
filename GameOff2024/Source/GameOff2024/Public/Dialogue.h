// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/RichTextBlock.h"
#include "Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UDialogue : public UUserWidget
{
	GENERATED_BODY()
public:
	// Sets the dialogue text to display
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogueText(const FText& NewText);

protected:
	// The RichTextBlock for displaying dialogue text
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* DialogueTextBlock;
};

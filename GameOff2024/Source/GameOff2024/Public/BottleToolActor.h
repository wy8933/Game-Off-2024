// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolActor.h"
#include "BottleToolActor.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API ABottleToolActor : public AToolActor
{
	GENERATED_BODY()
	

public:
	virtual void UseTool() override;

	UFUNCTION(BlueprintImplementableEvent)
		void ThrowBottle();
};

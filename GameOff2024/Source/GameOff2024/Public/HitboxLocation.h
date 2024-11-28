// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitboxLocation.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EHitboxLocation : uint8
{
	EHL_Head UMETA(DisplayName = "Head"),
	EHL_Body UMETA(DisplayName = "Body"),
	EHL_Limb UMETA(DisplayName = "Limb"),

	EHL_MAX UMETA(DisplayName = "DefaultMAX")
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "HitboxLocation.h"
#include "HitboxComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeHit, FVector, impactPoint);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF2024_API UHitboxComponent : public UBoxComponent
{



	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UHitboxComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void TakeDamage(FVector impactPoint);

	UPROPERTY(BlueprintAssignable)
	FOnTakeHit OnTakeHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHitboxLocation Location = EHitboxLocation::EHL_Body;
};



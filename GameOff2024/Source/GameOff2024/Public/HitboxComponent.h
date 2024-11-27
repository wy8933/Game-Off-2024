// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "HitboxComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeHit, int, Damage);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF2024_API UHitboxComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HitboxMesh;

public:	
	// Sets default values for this component's properties
	UHitboxComponent();

	int damageOnHit = 1;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void TakeDamage();

	UPROPERTY(BlueprintAssignable)
	FOnTakeHit OnTakeHit;
		
};

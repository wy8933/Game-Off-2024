// Fill out your copyright notice in the Description page of Project Settings.


#include "HitboxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UHitboxComponent::UHitboxComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//SetCollisionObjectType();
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// ...
}


// Called when the game starts
void UHitboxComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UHitboxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHitboxComponent::TakeDamage()
{
	if (OnTakeHit.IsBound())
	{
		OnTakeHit.Broadcast(damageOnHit);
	}
}
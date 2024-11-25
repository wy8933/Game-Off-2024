// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLight.h"

// Sets default values
APlayerLight::APlayerLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerLight::SetActive(bool Active)
{
	SetActorHiddenInGame(!Active);
	SetActorTickEnabled(Active);
}

void APlayerLight::ToggleLight(bool value)
{
	SetActorHiddenInGame(!value);
	SetActorTickEnabled(value);
}

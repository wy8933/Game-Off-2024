// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolActor.h"

// Sets default values
AToolActor::AToolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AToolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AToolActor::UseTool()
{

}

void AToolActor::SetActive(bool active)
{
	SetActorHiddenInGame(active);
	SetActorTickEnabled(active);
}


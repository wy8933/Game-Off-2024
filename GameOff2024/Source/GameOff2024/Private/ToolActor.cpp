// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolActor.h"

// Sets default values
AToolActor::AToolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
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
	
	//SetActorHiddenInGame(active);
	SetActorTickEnabled(active);
	VisualMesh->SetVisibility(active);
	OnToggleActive(active);
	//VisualMesh->bHiddenInGame = active;
	//Visible
}


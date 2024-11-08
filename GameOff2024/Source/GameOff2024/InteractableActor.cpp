// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableActor.h"
#include "Components/WidgetComponent.h"
#include "InteractionPromptWidget.h"


// Sets default values
AInteractableActor::AInteractableActor()
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
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	InteractPrompt = CreateWidget<UInteractionPromptWidget>(GetWorld()->GetFirstPlayerController(), UInteractionPromptWidget::StaticClass(), "Interaction Prompt");
	InteractPrompt->AddToViewport();
	//DisableInteractPrompt();
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::Interact()
{
	DisableInteractPrompt();
	Destroy();
}

void AInteractableActor::EnableInteractPrompt()
{
	InteractPrompt->SetVisibility(ESlateVisibility::Visible);
}

void AInteractableActor::DisableInteractPrompt()
{
	InteractPrompt->SetVisibility(ESlateVisibility::Hidden);
}

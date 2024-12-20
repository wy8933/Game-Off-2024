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

	UWidgetComponent* widget = GetComponentByClass<UWidgetComponent>();

	if (widget)
	{
		InteractPrompt = Cast<UInteractionPromptWidget>(widget->GetUserWidgetObject());
		DisableInteractPrompt();
	}

	SetWidgetPromptText();
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActor::SetWidgetPromptText()
{
	if (InteractPrompt)
	{
		InteractPrompt->InteractionType = InteractionType;
		InteractPrompt->SetPromptText();
	}
}

void AInteractableActor::Interact(AGameOff2024Character* interactor)
{
	if(bCanBeInteractedWith == false)
	{
		return;
	}

	InteractBP();
	if (bDestroyOnInteract) {
		DisableInteractPrompt();
		//Destroy();
	}
}

void AInteractableActor::EnableInteractPrompt()
{
	if (InteractPrompt)
	{
		if (bCanBeInteractedWith == true)
		{
			InteractPrompt->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AInteractableActor::DisableInteractPrompt()
{
	if (InteractPrompt)
	{
		InteractPrompt->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AInteractableActor::EnableInteraction()
{
	bCanBeInteractedWith = true;
}

void AInteractableActor::DisableInteraction()
{
	bCanBeInteractedWith = false;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionPromptWidget.h"
#include "GameOff2024Character.h"
#include "InteractableActor.generated.h"

UCLASS(BlueprintType)
class GAMEOFF2024_API AInteractableActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisualMesh;


public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = UI)
	FText InteractionType = FText::FromString("Interact");

public:	
	//Reference to the interaction prompt
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UInteractionPromptWidget* InteractPrompt;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AGameOff2024Character* interactor);
	virtual void EnableInteractPrompt();
	virtual void DisableInteractPrompt();
};

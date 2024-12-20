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

public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		FText InteractionType = FText::FromString("Interact");

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* VisualMesh;

	//Reference to the interaction prompt
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
		UInteractionPromptWidget* InteractPrompt;

	UPROPERTY(EditAnywhere)
		bool bDestroyOnInteract = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
		bool bCanBeInteractedWith = true;


	UFUNCTION(BlueprintImplementableEvent)
		void InteractBP();

	UFUNCTION(BlueprintCallable)
		void SetWidgetPromptText();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AGameOff2024Character* interactor);
	virtual void EnableInteractPrompt();
	virtual void DisableInteractPrompt();

	UFUNCTION(BlueprintCallable)
	void EnableInteraction();
	UFUNCTION(BlueprintCallable)
	void DisableInteraction();
};

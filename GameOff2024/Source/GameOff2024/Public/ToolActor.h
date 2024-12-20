// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolActor.generated.h"

UCLASS()
class GAMEOFF2024_API AToolActor : public AActor
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisualMesh;

	
public:	
	// Sets default values for this actor's properties
	AToolActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void UseTool();

	UFUNCTION(BlueprintCallable)
	void SetActive(bool active);

	UFUNCTION(BlueprintImplementableEvent)
	void OnToggleActive(bool active);
};

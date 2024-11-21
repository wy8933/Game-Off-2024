// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AmmoHUDWidget.h"
#include "HealthHUDWidget.h"
#include "BottlesHUDWidget.h"
#include "ToolActor.h"
#include "PlayerLight.h"
#include "GameOff2024Character.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, int, CurrentHealth, int, MaxHealth);

UCLASS(config=Game)
class AGameOff2024Character : public ACharacter
{
	GENERATED_BODY()

	class UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();

	class AInteractableActor* targetInteractable;

	void GetInteractableTarget();

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Crouch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	/** Heal Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseHealthItemAction;

	/** Swap Tool Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapToGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapToMagnifierAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapToBottleAction;

	/** Light Source Input Actions*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwapLightSourceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleLightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChargeLightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseToolAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadWeaponAction;

public:
	AGameOff2024Character();

protected:
	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float WalkSpeed = 600.0f;

	//** The value multiplied to the default speed while sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float MaxSprintSpeed = 900.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float MaxInteractionRange = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	int MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int CurrentHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tools")
	AToolActor* CurrentActiveTool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	AToolActor* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	AToolActor* Magnifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tools")
	AToolActor* Bottle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light Sources")
	APlayerLight* CurrentActiveLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Sources")
	APlayerLight* Flashlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Sources")
	APlayerLight* Lighter;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	class UInventory* Inventory;

	class UAmmoHUDWidget* AmmoHUD;
	class UHealthHUDWidget* HealthHUD;
	class UBottlesHUDWidget* BottlesHUD;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Sprint input */
	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);

	/** Called for crouch input */
	void ToggleCrouch(const FInputActionValue& Value);

	/** Called for Interact input*/
	void Interact(const FInputActionValue& Value);

	/** Called for healing input*/
	void UseHealthItem(const FInputActionValue& Value);

	/** Called for swapping tools*/
	void SwapToolGun(const FInputActionValue& Value);
	void SwapToolMagnifier(const FInputActionValue& Value);
	void SwapToolBottle(const FInputActionValue& Value);

	/** Called for light source actions*/
	void SwapLightSource(const FInputActionValue& Value);
	void ToggleLight(const FInputActionValue& Value);
	void ChargeLight(const FInputActionValue& Value);

	/** Called for aiming and using active tool*/
	void UseTool(const FInputActionValue& Value);
	void Aim(const FInputActionValue& Value);
	
	/** Called for gun reload action*/
	void ReloadWeapon(const FInputActionValue& Value);

	//Sets Up Hud
	void SetUpHUD();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Amount);

	UFUNCTION(BlueprintCallable)
	bool TryRestoreHealth(int Amount);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
};


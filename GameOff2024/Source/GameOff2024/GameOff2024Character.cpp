// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOff2024Character.h"
#include "GameOff2024Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractableActor.h"
#include "Inventory.h"
#include "PlayerHUD.h"
#include "HealthPickup.h"
#include "Components/WidgetComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGameOff2024Character

AGameOff2024Character::AGameOff2024Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AGameOff2024Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	Inventory = NewObject<UInventory>((UObject*)GetTransientPackage(), UInventory::StaticClass());

	SetUpHUD();
}

void AGameOff2024Character::TakeDamage(int Amount)
{
	CurrentHealth -= Amount;

	if (CurrentHealth <= 0)
	{
		//Death
	}

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

/// <summary>
/// Returns false if the player is already at full health
/// </summary>
/// <param name="Amount">The amount of health to restore</param>
/// <returns>bool</returns>
bool AGameOff2024Character::TryRestoreHealth(int Amount)
{

	if (CurrentHealth >= MaxHealth)
	{
		return false;
	}

	CurrentHealth += Amount;

	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	return true;
}

///////////////////////////////////////////////////////////////////////////// HUD

void AGameOff2024Character::SetUpHUD()
{

	APlayerController* PlayerController = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	if (!PlayerController)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to get Player Controller"));
		}
		return;
	}

	APlayerHUD* HUD = Cast<APlayerHUD>(PlayerController->GetHUD());
	if (!HUD)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to cast HUD to APlayerHUD"));
		}
		return;
	}

	if (HUD)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Succefully created HUD"));
		}
		AmmoHUD = HUD->AmmoHUD;

		Inventory->OnAmmoChanged.AddDynamic(AmmoHUD, &UAmmoHUDWidget::UpdateHUD);

		HealthHUD = HUD->HealthHUD;

		this -> OnHealthChanged.AddDynamic(HealthHUD, &UHealthHUDWidget::UpdateHUDHealthBar);
		Inventory->OnHealthItemsChanged.AddDynamic(HealthHUD, &UHealthHUDWidget::UpdateHUDHealthItemsCarried);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AGameOff2024Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGameOff2024Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGameOff2024Character::Look);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AGameOff2024Character::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AGameOff2024Character::StopSprinting);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGameOff2024Character::ToggleCrouch);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGameOff2024Character::Interact);

		//UsingHealhtItems
		EnhancedInputComponent->BindAction(UseHealthItemAction, ETriggerEvent::Started, this, &AGameOff2024Character::UseHealthItem);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	WalkSpeed = CharacterMovement->MaxWalkSpeed;
}


void AGameOff2024Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		
	}
}

void AGameOff2024Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGameOff2024Character::Sprint(const FInputActionValue& Value)
{
	IsSprinting = true;
	CharacterMovement->MaxWalkSpeed = MaxSprintSpeed;
}

void AGameOff2024Character::StopSprinting(const FInputActionValue& Value)
{
	IsSprinting = false;
	CharacterMovement->MaxWalkSpeed = WalkSpeed;
}

void AGameOff2024Character::ToggleCrouch(const FInputActionValue& Value)
{
	if (bIsCrouched == false)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AGameOff2024Character::Interact(const FInputActionValue& Value)
{
	if (targetInteractable != nullptr)
	{
		targetInteractable->Interact(this);
	}
}

void AGameOff2024Character::UseHealthItem(const FInputActionValue& Value)
{
	if (Inventory->HealthItemsCarried > 0)
	{
		if (TryRestoreHealth(AHealthPickup::HealthRestoreAmount))
		{
			Inventory->TryRemoveHealthItem();
			Inventory->OnHealthItemsChanged.Broadcast(Inventory->HealthItemsCarried);
		}
	}
}

void AGameOff2024Character::GetInteractableTarget()
{
	FVector CameraLocation = FirstPersonCameraComponent->GetComponentLocation();
	FRotator CameraRotation = FirstPersonCameraComponent->GetComponentRotation();
	AInteractableActor* interactableActor = nullptr;

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	//RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	//call GetWorld() from within an actor extending class
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,		//result
		CameraLocation,	//start
		CameraLocation + (CameraRotation.Vector() * MaxInteractionRange), //end
		ECC_Pawn, //collision channel
		RV_TraceParams
	);

	if (RV_Hit.bBlockingHit)//did hit something? (bool)
	{
		AActor* actor = RV_Hit.GetActor(); //the hit actor if there is one

		//UE_LOG(LogTemp, Display, TEXT("Hit"));

		if (actor->GetClass()->IsChildOf(AInteractableActor::StaticClass()))
		{
			interactableActor = (AInteractableActor*)actor;

		}
	}

	if (targetInteractable != interactableActor)
	{

		if (targetInteractable != nullptr)
		{
			//disable previous interaction prompt
			targetInteractable->DisableInteractPrompt();
		}

		targetInteractable = interactableActor;

		if (targetInteractable != nullptr)
		{
			//enable new interaction prompt
			targetInteractable->EnableInteractPrompt();
		}
	}
}

void AGameOff2024Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetInteractableTarget();
}
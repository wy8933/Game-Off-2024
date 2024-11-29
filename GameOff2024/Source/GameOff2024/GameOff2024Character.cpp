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
#include "BottleToolActor.h"
#include "MagnifierToolActor.h"
#include "GunToolActor.h"
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

	TArray<AActor*> children;
	this->GetAllChildActors(children);

	//FirstPersonCameraComponent->GetChildrenComponents(true, children);//GetAllChildActors(children);
	
	for (int i = 0; i < children.Num(); i++)
	{
		if (children[i]->GetClass() == ABottleToolActor::StaticClass())
		{
			Bottle = Cast<ABottleToolActor>(children[i]);
			Bottle->SetActive(false);
		}
		else if (children[i]->GetClass() == AMagnifierToolActor::StaticClass())
		{
			Magnifier = Cast<AMagnifierToolActor>(children[i]);
			Magnifier->SetActive(false);
		}
		else if (children[i]->GetClass() == AGunToolActor::StaticClass())
		{
			Gun = Cast<AGunToolActor>(children[i]);
			Gun->SetActive(false);
			Gun->Inventory = Inventory;
		}
	}

	if (Flashlight) {
		CurrentActiveLight = Flashlight;
	}

	SetUpHUD();
}

void AGameOff2024Character::TakeDamage(int Amount)
{
	CurrentHealth -= Amount;

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Player get hit");
	}
	//Death
	if (CurrentHealth <= 0)
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Player HP is 0");
		}
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

		if (AmmoHUD)
		{
			Inventory->OnAmmoChanged.AddDynamic(AmmoHUD, &UAmmoHUDWidget::UpdateHUD);
		}

		HealthHUD = HUD->HealthHUD;

		if (HealthHUD)
		{
			this->OnHealthChanged.AddDynamic(HealthHUD, &UHealthHUDWidget::UpdateHUDHealthBar);
			Inventory->OnHealthItemsChanged.AddDynamic(HealthHUD, &UHealthHUDWidget::UpdateHUDHealthItemsCarried);
		}

		BottlesHUD = HUD->BottlesHUD;

		if (BottlesHUD)
		{
			Inventory->OnBottlesCarriedChanged.AddDynamic(BottlesHUD, &UBottlesHUDWidget::UpdateHUD);
		}
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

		//Using Healht Items
		EnhancedInputComponent->BindAction(UseHealthItemAction, ETriggerEvent::Started, this, &AGameOff2024Character::UseHealthItem);

		//Swapping Items
		EnhancedInputComponent->BindAction(SwapToGunAction, ETriggerEvent::Started, this, &AGameOff2024Character::SwapToolGun);
		EnhancedInputComponent->BindAction(SwapToMagnifierAction, ETriggerEvent::Started, this, &AGameOff2024Character::SwapToolMagnifier);
		EnhancedInputComponent->BindAction(SwapToBottleAction, ETriggerEvent::Started, this, &AGameOff2024Character::SwapToolBottle);

		//Light Actions
		EnhancedInputComponent->BindAction(SwapLightSourceAction, ETriggerEvent::Started, this, &AGameOff2024Character::SwapLightSource);
		EnhancedInputComponent->BindAction(ToggleLightAction, ETriggerEvent::Started, this, &AGameOff2024Character::ToggleLight);
		EnhancedInputComponent->BindAction(ChargeLightAction, ETriggerEvent::Started, this, &AGameOff2024Character::ChargeLight);

		//Using Tools
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AGameOff2024Character::Aim);
		EnhancedInputComponent->BindAction(UseToolAction, ETriggerEvent::Started, this, &AGameOff2024Character::UseTool);

		//Weapon Reload
		EnhancedInputComponent->BindAction(ReloadWeaponAction, ETriggerEvent::Started, this, &AGameOff2024Character::ReloadWeapon);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	//Set Walk Speed
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

void AGameOff2024Character::SwapToolGun(const FInputActionValue& Value)
{
	if (!Gun)
	{
		return;
	}

	if (CurrentActiveTool != Gun)
	{
		if (CurrentActiveTool)
		{
			CurrentActiveTool->SetActive(false);
		}
		CurrentActiveTool = Gun;
		CurrentActiveTool->SetActive(true);
	}
}

void AGameOff2024Character::SwapToolMagnifier(const FInputActionValue& Value)
{
	if (!Magnifier)
	{
		return;
	}

	if (Inventory->HasMagnifier == false)
	{
		return;
	}

	if (CurrentActiveTool != Magnifier)
	{
		if (CurrentActiveTool)
		{
			CurrentActiveTool->SetActive(false);
		}
		CurrentActiveTool = Magnifier;
		CurrentActiveTool->SetActive(true);
	}
}

void AGameOff2024Character::SwapToolBottle(const FInputActionValue& Value)
{
	if (!Bottle)
	{
		return;
	}

	if (Inventory->BottlesCarried <= 0)
	{
		return;
	}

	if (CurrentActiveTool != Bottle)
	{
		if (CurrentActiveTool)
		{
			CurrentActiveTool->SetActive(false);
		}
		CurrentActiveTool = Bottle;
		CurrentActiveTool->SetActive(true);
	}
}

void AGameOff2024Character::SwapLightSource(const FInputActionValue& Value)
{
	LightSourceOn = true;
	if (CurrentActiveLight)
	{
		CurrentActiveLight->SetActive(false);

		if (Flashlight && CurrentActiveLight != Flashlight)
		{
			CurrentActiveLight = Flashlight;
		}
		else
		{
			if (Lighter)
			{
				CurrentActiveLight = Lighter;
			}
		}

		CurrentActiveLight->SetActive(true);
	}
}

void AGameOff2024Character::ToggleLight(const FInputActionValue& Value)
{
	LightSourceOn = !LightSourceOn;
	if (CurrentActiveLight)
	{
		CurrentActiveLight->ToggleLight(LightSourceOn);
	}
}

void AGameOff2024Character::ChargeLight(const FInputActionValue& Value)
{
	if (!Flashlight && CurrentActiveLight != Flashlight)
	{
		return;
	}

	LightSourceOn = true;
}

void AGameOff2024Character::Aim(const FInputActionValue& Value)
{

}

void AGameOff2024Character::UseTool(const FInputActionValue& Value)
{
	if (CurrentActiveTool)
	{
		CurrentActiveTool->UseTool();
	}
}

void AGameOff2024Character::ReloadWeapon(const FInputActionValue& Value)
{
	if (CurrentActiveTool != Gun)
	{
		return;
	}

	Gun->Reload();
	//Inventory->TryReloadWeapon();
}

void AGameOff2024Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetInteractableTarget();
}

/////////////////////////////////////////////// Sub Functions

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
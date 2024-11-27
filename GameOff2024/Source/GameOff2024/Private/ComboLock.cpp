#include "ComboLock.h"
#include "ComboLockManager.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
AComboLock::AComboLock()
{
	CurrentNumber = 0;
}

// Called when the game starts or when spawned
void AComboLock::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the number display
	UpdateNumberDisplay();
}

// Called when the player interacts with this lock
void AComboLock::Interact(AGameOff2024Character* interactor)
{
	// Rotate the lock dial
	RotateLock();

	if (!NumberDisplay)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NumberDisplay is not assigned!"));
		}
	}
}

// Rotate the dial to the next number
void AComboLock::RotateLock()
{
	// Increment the current number
	CurrentNumber++;

	// Wrap around if the number exceeds the maximum
	if (CurrentNumber > MaxNumber)
	{
		CurrentNumber = 0;
	}

	// Play the rotation sound if set
	if (RotateSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RotateSound, GetActorLocation());
	}

	// Update the number display
	UpdateNumberDisplay();

	// Notify the manager to check the combination
	if (ComboLockManager)
	{
		ComboLockManager->CheckCombination();
	}

	// Print debug message for testing
	if (GEngine)
	{
		FString DebugMessage = FString::Printf(TEXT("Current Number: %d"), CurrentNumber);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, DebugMessage);
	}
}

// Get the current number of the dial
int32 AComboLock::GetCurrentNumber() const
{
	return CurrentNumber;
}

// Updates the visual display of the current number
void AComboLock::UpdateNumberDisplay()
{
	if (NumberDisplay)
	{
		NumberDisplay->SetText(FText::AsNumber(CurrentNumber));
	}
}

void AComboLock::SetComboLockManager(AComboLockManager* Manager)
{
	if (Manager)
	{
		ComboLockManager = Manager;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ComboLockManager set successfully!"));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to set ComboLockManager!"));
		}
	}
}

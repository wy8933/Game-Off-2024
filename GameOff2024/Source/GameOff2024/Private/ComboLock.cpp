#include "ComboLock.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
AComboLock::AComboLock()
{
	// Enable ticking
	PrimaryActorTick.bCanEverTick = false;

	// Set the default current number to 0
	CurrentNumber = 0;

	// Create a Text Render Component for displaying the current number
	NumberDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NumberDisplay"));
	NumberDisplay->SetupAttachment(RootComponent);
	NumberDisplay->SetHorizontalAlignment(EHTA_Center);
	NumberDisplay->SetText(FText::FromString(TEXT("0")));
	NumberDisplay->SetWorldSize(50.0f);
	NumberDisplay->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
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
		// Update the displayed text
		NumberDisplay->SetText(FText::AsNumber(CurrentNumber));
	}
}

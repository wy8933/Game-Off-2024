
#pragma once

#include "CoreMinimal.h"
#include "../InteractableActor.h"
#include "ComboLock.generated.h"

/**
 *  
 */
UCLASS()
class GAMEOFF2024_API AComboLock : public AInteractableActor
{
	GENERATED_BODY()


public:
	AComboLock();

	virtual void Interact(AGameOff2024Character* interactor) override;

	// Rotate the dial to the next number
	UFUNCTION(BlueprintCallable, Category = "Combo Lock")
	void RotateLock();

	// Get the current number of the dial
	UFUNCTION(BlueprintCallable, Category = "Combo Lock")
	int32 GetCurrentNumber() const;

protected:
	// Called when the game starts or the actor is spawned
	virtual void BeginPlay() override;

	// The current number displayed on the dial (0-9)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combo Lock")
	int32 CurrentNumber;

	// The maximum number the dial can reach before looping back to 0
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo Lock")
	int32 MaxNumber = 9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Lock")
	class UTextRenderComponent* NumberDisplay;

	// Sound to play when the dial is rotated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Lock")
	class USoundBase* RotateSound;

private:
	// Updates the visual display of the current number
	void UpdateNumberDisplay();

};

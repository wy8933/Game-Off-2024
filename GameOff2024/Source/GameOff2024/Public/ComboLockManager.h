#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComboLockManager.generated.h"

UCLASS()
class GAMEOFF2024_API AComboLockManager : public AActor
{
    GENERATED_BODY()
     
public:
    AComboLockManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Array to store the locks
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Lock Manager")
    TArray<AComboLock*> Locks;

    // The correct password combination
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Lock Manager")
    TArray<int32> CorrectCombination;

    // Bool to check if the combination is correct
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo Lock Manager")
    bool bIsPasswordCorrect;

    // Check the combination
    UFUNCTION(BlueprintCallable, Category = "Combo Lock Manager")
    void CheckCombination();

    UFUNCTION(BlueprintCallable, Category = "Combo Lock")
    void AddLock(AComboLock* Lock);
};

#include "ComboLock.h"
#include "ComboLockManager.h"
#include "Kismet/GameplayStatics.h"

AComboLockManager::AComboLockManager()
{
    PrimaryActorTick.bCanEverTick = true;

    bIsPasswordCorrect = false;
}

void AComboLockManager::BeginPlay()
{
    Super::BeginPlay();

    // Make sure the number of locks matches the correct combination
    if (Locks.Num() != CorrectCombination.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Number of locks does not match the correct combination!"));
    }
}

void AComboLockManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AComboLockManager::AddLock(AComboLock* Lock)
{
    if (Lock)
    {
        // Add the lock to the list
        Locks.Add(Lock);

        // Set the lock's manager 
        Lock->SetComboLockManager(this);
    }
}

void AComboLockManager::CheckCombination()
{
    if (Locks.Num() != CorrectCombination.Num())
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Lock num and combination num are not the same");
        }
        return;
    }

    bIsPasswordCorrect = true;

    for (int32 i = 0; i < Locks.Num(); i++)
    {
        if (Locks[i]->GetCurrentNumber() != CorrectCombination[i])
        {
            bIsPasswordCorrect = false; // If one lock is incorrect, the password is wrong
            break;
        }
    }
}

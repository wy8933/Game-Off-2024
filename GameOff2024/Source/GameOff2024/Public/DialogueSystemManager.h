#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.h"
#include "DialogueSystemManager.generated.h"

UCLASS(Blueprintable)
class GAMEOFF2024_API UDialogueSystemManager : public UObject
{
    GENERATED_BODY()

public:
    int32 CurrentNodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueDataTable;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    FDialogueNode GetCurrentDialogueNode();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void ProgressToNextNode();

};

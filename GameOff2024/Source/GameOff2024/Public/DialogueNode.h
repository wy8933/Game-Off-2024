#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.generated.h"

USTRUCT(BlueprintType)
struct FDialogueNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NextNodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, int32> Choices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpeakerName;

    FDialogueNode()
        : NodeID(-1), NextNodeID(-1) {}
};

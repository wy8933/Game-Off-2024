#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.generated.h"

USTRUCT(BlueprintType)
struct FDialogueNode: public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NextNodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpeakerName;

    FDialogueNode()
        : NextNodeID(-1) {}
};

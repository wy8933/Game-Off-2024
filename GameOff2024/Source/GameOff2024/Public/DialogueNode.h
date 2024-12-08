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
    FText ChineseText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FrenchText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpanishText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NextNodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* DialogueAudio;

    FDialogueNode()
        : NextNodeID(-1), DialogueAudio(nullptr) {}
};

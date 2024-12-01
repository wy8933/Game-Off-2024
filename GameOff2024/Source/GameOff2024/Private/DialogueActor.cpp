#include "DialogueActor.h"
#include "Dialogue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"

ADialogueActor::ADialogueActor()
{
    // Set default values
    DialogueDataTable = nullptr;
    CurrentNodeID = 0;
    DialogueWidgetInstance = nullptr;
    bIsDialogueActive = false;

    // Create the audio component
    DialogueAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DialogueAudioComponent"));
    DialogueAudioComponent->bAutoActivate = false; // Do not auto-play
    DialogueAudioComponent->OnAudioFinished.AddDynamic(this, &ADialogueActor::OnDialogueAudioFinished);
}

void ADialogueActor::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the widget class is set before creating the widget
    if (DialogueWidgetClass)
    {
        DialogueWidgetInstance = CreateWidget<UDialogue>(GetWorld(), DialogueWidgetClass);
        if (DialogueWidgetInstance)
        {
            DialogueWidgetInstance->AddToViewport();
            DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if (DialogueDataTable == nullptr && GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dialogue DataTable is not set or failed to load!"));
    }
}

void ADialogueActor::Interact(AGameOff2024Character* interactor)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor interacted"));
    }

    if (DialogueDataTable && DialogueWidgetInstance)
    {
        // Start the dialogue only if it's not already active
        if (!bIsDialogueActive)
        {
            StartDialogue();
        }
    }
}

/// <summary>
/// Start play the dialogue
/// </summary>
void ADialogueActor::StartDialogue()
{
    // Reset state and begin dialogue
    bIsDialogueActive = true;
    CurrentNodeID = 0;

    if (DialogueAudioComponent && DialogueAudioComponent->IsPlaying())
    {
        DialogueAudioComponent->Stop(); // Stop any audio still playing
    }

    DisplayCurrentNode();
}

/// <summary>
/// Display the subtitle for current dialogue and play the audio
/// </summary>
void ADialogueActor::DisplayCurrentNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();

    // Show the dialogue widget and update the text
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Visible);
        UDialogue* DialogueWidget = Cast<UDialogue>(DialogueWidgetInstance);
        DialogueWidget->UpdateDialogue(CurrentNode.SpeakerName, CurrentNode.DialogueText);
    }

    // Play the audio for the current node, if available
    if (CurrentNode.DialogueAudio && DialogueAudioComponent)
    {
        DialogueAudioComponent->SetSound(CurrentNode.DialogueAudio);
        DialogueAudioComponent->Play();
    }
    else
    {
        OnDialogueAudioFinished(); // Automatically progress if no audio
    }
}

/// <summary>
/// Get the current node for Dialogue
/// </summary>
/// <returns>the current dialogue node</returns>
FDialogueNode ADialogueActor::GetCurrentDialogueNode()
{
    if (!DialogueDataTable)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Data table found"));
        }
        return FDialogueNode();
    }

    // Find the node with the correctID
    FName RowName = FName(*FString::FromInt(CurrentNodeID));
    FDialogueNode* Node = DialogueDataTable->FindRow<FDialogueNode>(RowName, TEXT("Lookup Dialogue Node"));

    // Return the node found or print debug message
    if (Node)
    {
        return *Node;
    }
    else
    {
        if (GEngine)
        {
            FString ErrorMessage = FString::Printf(TEXT("Node with ID %d not found in DialogueDataTable"), CurrentNodeID);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *ErrorMessage);
        }
        return FDialogueNode();
    }
}

/// <summary>
/// Progress to the next node and end dialogue when there is none
/// </summary>
void ADialogueActor::ProgressToNextNode()
{
    FDialogueNode CurrentNode = GetCurrentDialogueNode();
    CurrentNodeID = CurrentNode.NextNodeID;

    // Check if end of the dialogue is reached
    if (CurrentNodeID == -1)
    {
        EndDialogue();
    }
    else
    {
        DisplayCurrentNode();
    }
}

void ADialogueActor::OnDialogueAudioFinished()
{
    if (bIsDialogueActive)
    {
        ProgressToNextNode();
    }
}

/// <summary>
/// End the current dialogue
/// </summary>
void ADialogueActor::EndDialogue()
{
    if (DialogueWidgetInstance)
    {
        DialogueWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
    }
    bIsDialogueActive = false;
}

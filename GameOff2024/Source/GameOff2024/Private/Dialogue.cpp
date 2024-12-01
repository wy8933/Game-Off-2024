
#include "Dialogue.h"

void UDialogue::SetDialogueText(const FText& NewText)
{
	if (DialogueTextBlock)
	{
		// Set the text in the RichTextBlock
		DialogueTextBlock->SetText(NewText);
	}
}

void UDialogue::UpdateDialogue(FText SpeakerName, FText DialogueText) {
	// Format the dialogue to use rich text
	FText FormattedText = FText::Format(FText::FromString("<Name>{0}</>: {1}"), SpeakerName, DialogueText);
	SetDialogueText(FormattedText);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FormattedText.ToString());
	}
}

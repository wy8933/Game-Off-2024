
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
	//format the dialogue to use rich text
	FText FormattedText = FText::Format(FText::FromString("<Name>{0}</> {1}"), SpeakerName, DialogueText);
	DialogueTextBlock->SetText(FormattedText);
}

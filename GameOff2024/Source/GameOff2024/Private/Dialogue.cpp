
#include "Dialogue.h"

void UDialogue::SetDialogueText(const FText& NewText)
{
	if (DialogueTextBlock)
	{
		// Set the text in the RichTextBlock
		DialogueTextBlock->SetText(NewText);
	}
}

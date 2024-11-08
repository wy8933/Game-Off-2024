// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionPromptWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"


void UInteractionPromptWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	auto MyCanvas = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());

	if (MyCanvas)
	{
		auto TextBlock = WidgetTree->ConstructWidget<UTextBlock>();
		MyCanvas->AddChild(TextBlock);
		const auto tempSlot = Cast<UCanvasPanelSlot>(TextBlock->Slot);
		if (tempSlot)
		{
			tempSlot->SetAutoSize(true);
			tempSlot->SetOffsets(FMargin(0, 0));
			tempSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		}
		WidgetTree->RootWidget = MyCanvas;
	}
}
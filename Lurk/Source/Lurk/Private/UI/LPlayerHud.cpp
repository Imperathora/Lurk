// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LPlayerHud.h"

#include <Blueprint/UserWidget.h>
#include "UI/LInteractionWidget.h"

void ALPlayerHud::BeginPlay()
{
	Super::BeginPlay();

	if (ULInteractionWidget* const InteractionWidget = CreateWidget<ULInteractionWidget>(PlayerOwner, InteractionPrompt))
	{
		InteractionWidget->AddToViewport();
	}
}

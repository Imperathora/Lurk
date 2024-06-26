// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LInteractionWidget.h"

#include <Components/TextBlock.h>

#include "Systems/Interaction/LInteractableComponent.h"
#include "Systems/Interaction/LInteractorComponent.h"


void ULInteractionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ensure(InteractionText))
    {
        InteractionText->TextDelegate.BindDynamic(this, &ULInteractionWidget::GetInteractionText);
        InteractionText->SynchronizeProperties();
    }
}

FText ULInteractionWidget::GetInteractionText()
{
    const APlayerController* OwningPlayer = GetOwningPlayer();
    const APawn* PlayerPawn = OwningPlayer ? OwningPlayer->GetPawn() : nullptr;
    const ULInteractorComponent* InteractorComponent = PlayerPawn ? PlayerPawn->FindComponentByClass<ULInteractorComponent>() : nullptr;
    const ULInteractableComponent* InteractionTarget = InteractorComponent ? InteractorComponent->GetInteractionTarget() : nullptr;

    return InteractionTarget ? InteractionTarget->GetInteractionText() : FText::GetEmpty();
}

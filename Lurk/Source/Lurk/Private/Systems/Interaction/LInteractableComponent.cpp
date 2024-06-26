// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LInteractableComponent.h"

bool ULInteractableComponent::TryInteract()
{
	if (!OnInteract.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to interact with actor (%s) - no interaction delegate bound"), *GetOwner()->GetHumanReadableName());
		return false;
	}

	const bool bCanInteract = !CanInteract.IsBound() || CanInteract.Execute();
	if (bCanInteract)
	{
		OnInteract.Execute();
	}

	return bCanInteract;
}

FText ULInteractableComponent::GetInteractionText() const
{
	const FText ActionText = GetInteractText.IsBound() ? GetInteractText.Execute() : NSLOCTEXT("Lurk", "InteractionDefaultAction", "interact with this object");
	
	return FText::Format(NSLOCTEXT("Lurk", "InteractionPrompt", "Press E to {0}"), ActionText);
}


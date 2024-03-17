// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LInteractionComponent.h"

bool ULInteractionComponent::TryInteract()
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


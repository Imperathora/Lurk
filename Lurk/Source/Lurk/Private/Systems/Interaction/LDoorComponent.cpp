// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Interaction/LDoorComponent.h"
#include <Systems/Interaction/LInteractableComponent.h>

ULDoorComponent::ULDoorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetOwner()->GetActorQuat();

	if (ULInteractableComponent* InteractableComponent = GetOwner()->FindComponentByClass<ULInteractableComponent>())
	{
		InteractableComponent->OnInteract.BindUObject(this, &ThisClass::OnDoorInteraction);
		InteractableComponent->GetInteractText.BindUObject(this, &ThisClass::GetInteractionText);
	}
}

void ULDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const FQuat CurrentRotation = GetOwner()->GetActorQuat();
	const FQuat TargetRotation = GetTargetRotation();

	FQuat NewRotation;

	if (CurrentRotation.Equals(TargetRotation))
	{
		NewRotation = TargetRotation;
	}
	else
	{
		NewRotation = FQuat::Slerp(CurrentRotation, TargetRotation, OpenSpeed * DeltaTime);
	}

	GetOwner()->SetActorRotation(NewRotation);
}

FText ULDoorComponent::GetInteractionText() const
{
	switch (TargetState)
	{
	case EDoorState::Closed:
		return NSLOCTEXT("Lurk", "DoorInteractionOpen", "open the door");

	case EDoorState::Opened:
		return NSLOCTEXT("Lurk", "DoorInteractionClose", "close the door");

	default:
		checkNoEntry();
		return {};
	}
}

void ULDoorComponent::OnDoorInteraction()
{
	switch (TargetState)
	{
	case EDoorState::Closed:
		TargetState = EDoorState::Opened;
		break;

	case EDoorState::Opened:
		TargetState = EDoorState::Closed;
		break;

	default:
		checkNoEntry();
	}
}

FQuat ULDoorComponent::GetTargetRotation() const
{
	switch (TargetState)
	{
	case EDoorState::Closed:
		return InitialRotation;

	case EDoorState::Opened:
		return InitialRotation * FQuat::MakeFromEuler(OpenDelta);

	default:
		checkNoEntry();
		return {};
	}
}


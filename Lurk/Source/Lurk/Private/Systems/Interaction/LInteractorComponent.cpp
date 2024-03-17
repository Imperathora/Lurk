// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LInteractorComponent.h"

#include <Kismet/KismetSystemLibrary.h>

#include "Systems/LCharacter.h"
#include "Systems/Interaction/LInteractionComponent.h"


ULInteractorComponent::ULInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ALCharacter* CharacterOwner = GetOwner<ALCharacter>())
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(CharacterOwner->InputComponent);

		EnhancedInputComponent->BindAction(CharacterOwner->GetInteractAction(), ETriggerEvent::Triggered, this, &ULInteractorComponent::PerformInteraction);
	}
}

void ULInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateInteractionCandidates();
}

void ULInteractorComponent::UpdateInteractionCandidates()
{
}

void ULInteractorComponent::PerformInteraction()
{
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LItemComponent.h"
#include <Systems/Interaction/LInteractableComponent.h>
#include "DataAssets/LItemDataAsset.h"

ULItemComponent::ULItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULItemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ULInteractableComponent* InteractableComponent = GetOwner()->FindComponentByClass< ULInteractableComponent>())
	{
		InteractableComponent->OnInteract.BindUObject(this, &ThisClass::ItemInteraction);
		InteractableComponent->GetInteractText.BindUObject(this, &ThisClass::GetInteractionText);
	}
}

void ULItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FText ULItemComponent::GetInteractionText() const
{
	if (ItemData != nullptr)
	{
		return NSLOCTEXT("Lurk", "PickUpItem", "pick up pick up {0}"), ItemData->GetName();
	}	

	return NSLOCTEXT("Lurk", "PickUpItem", "pick up item"); 
}

int32 ULItemComponent::GetItemInventoryWidth() const
{
	if (ensure(IsValid(ItemData)))
	{
		return ItemData->GetWidth();
	}

	return 0;
}

int32 ULItemComponent::GetItemInventoryHeight() const
{
	if (ensure(IsValid(ItemData)))
	{
		return ItemData->GetHeight();
	}

	return 0;
}

void ULItemComponent::ItemInteraction()
{
	GetOwner()->Destroy();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("pickup"));
}

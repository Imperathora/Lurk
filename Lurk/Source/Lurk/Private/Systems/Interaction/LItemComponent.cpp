// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LItemComponent.h"
#include <Systems/Interaction/LInteractableComponent.h>
#include "DataAssets/LItemDataAsset.h"
#include "Systems/LCharacter.h"
#include <Framework/LPlayerController.h>

#include "Systems/Inventory/LInventoryComponent.h"

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
		return NSLOCTEXT("Lurk", "PickUpItem", "pick up pick up {0}"), ItemData->GetItemName();
	}	

	return NSLOCTEXT("Lurk", "PickUpItem", "pick up item"); 
}

void ULItemComponent::ItemInteraction()
{
	if (ALPlayerController* PlayerController = CastChecked<ALPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if(ALCharacter* Character = CastChecked<ALCharacter>(PlayerController->GetCharacter()))
		{
			ULInventoryComponent* InventoryComponent = Character ? Character->FindComponentByClass<ULInventoryComponent>() : nullptr;

			if(InventoryComponent->PickUp(this))
			{
				GetOwner()->Destroy();
				
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("picked up"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("pickup not successful"));
			}
		}
	}
}

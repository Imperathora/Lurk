// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Inventory/LInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/LItemDataAsset.h"
#include "Framework/LPlayerController.h"
#include "Systems/LCharacter.h"
#include "Systems/Interaction/LItemComponent.h"
#include "UI/LUIInventory.h"

ULInventoryComponent::ULInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ALCharacter* CharacterOwner = GetOwner<ALCharacter>())
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(
			CharacterOwner->InputComponent);

		EnhancedInputComponent->BindAction(CharacterOwner->GetOpenInventoryAction(), ETriggerEvent::Started, this,
		                                   &ULInventoryComponent::OpenInventory);
	}
}


void ULInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool ULInventoryComponent::PickUp(ULItemComponent* ItemToPickUp)
{
	int32 index = -1;
	int32 remaining = -2;
	int32 empty = -1;
	ULItemDataAsset* dataAsset = ItemToPickUp->GetDataAsset();
	while (index < MaxSize)
	{
		if (!IsKeyFull(index, remaining))
		{
			if (remaining == -1)
			{
				if (remaining == empty)
				{
					if (empty == -1)
					{
						empty = index;
					}
				}
			}
		}
		++index;
	}
	if (empty != -1)
	{
		Inventory.Add(empty, dataAsset);
		return true;
	}
	return false;
}

bool ULInventoryComponent::IsKeyFull(const int32& Key, int32& Remaining)
{
	if (!Inventory.Find(Key))
	{
		Remaining = -1;
		return false;
	}
	return true;
}

void ULInventoryComponent::ItemAdded(int32 SlotKey, ULItemDataAsset* SlotValue)
{
	Inventory.Add(SlotKey, SlotValue);
	
	if (InventoryWidget)
	{
		InventoryWidget->OnItemAdded.Broadcast(SlotKey, SlotValue);
	}
}

void ULInventoryComponent::ItemRemoved(int32 SlotKey)
{
	Inventory.Remove(SlotKey);

	if (InventoryWidget)
	{
		InventoryWidget->OnItemRemoved.Broadcast(SlotKey);
	}
}

void ULInventoryComponent::ItemDropped(ULItemDataAsset* ItemDropped)
{
	if (ALCharacter* CharacterOwner = GetOwner<ALCharacter>())
	{
		FVector ActorForwardVector = CharacterOwner->GetActorForwardVector();
		FVector ActorLocation = CharacterOwner->GetActorLocation();

		FVector Start = ActorForwardVector * 300.f + ActorLocation;
		FVector End = ActorForwardVector * 300.f + ActorLocation - FVector(0, 0, 500);

		FVector BoxHalfSize(15.0f, 15.0f, 15.0f);

		FQuat BoxRotation = FQuat::Identity;

		FCollisionQueryParams TraceParams;
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(CharacterOwner);

		FCollisionResponseParams ResponseParams;

		FHitResult HitResult;

		bool bHit = GetWorld()->SweepSingleByChannel(
			HitResult,
			Start,
			End,
			BoxRotation,
			ECC_Visibility,
			FCollisionShape::MakeBox(BoxHalfSize),
			TraceParams,
			ResponseParams
		);

		// Check if we hit something
		if (bHit)
		{
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<AActor>(ItemDropped->GetClass(), HitResult.Location, FRotator::ZeroRotator,
			                               SpawnParams);
		}
		DrawDebugBox(GetWorld(), HitResult.Location, BoxHalfSize, BoxRotation, FColor::Red, false, 5.0f);

		if (InventoryWidget)
		{
			InventoryWidget->OnItemDropped.Broadcast(ItemDropped);
		}
	}
}

void ULInventoryComponent::OpenInventory()
{
	ALCharacter* CharacterOwner = GetOwner<ALCharacter>();

	if (!IsValid(CharacterOwner)) { return; }

	ALPlayerController* PlayerController = Cast<ALPlayerController>(CharacterOwner->GetController());

	if (!IsValid(PlayerController)) { return; }


	if (!InventoryWidget)
	{
		if (InventoryWidgetClass)
		{
			InventoryWidget = CreateWidget<ULUIInventory>(PlayerController, InventoryWidgetClass);
			if (InventoryWidget)
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeGameAndUI());
				InventoryWidget->SetInventory(Inventory);
				InventoryWidget->SetMaxSize(MaxSize);
				InventoryWidget->AddToViewport();
				
				InventoryWidget->OnItemAdded.AddDynamic(InventoryWidget, &ULUIInventory::ItemAdded);
				InventoryWidget->OnItemDropped.AddDynamic(InventoryWidget, &ULUIInventory::ItemDropped);
				InventoryWidget->OnItemRemoved.AddDynamic(InventoryWidget, &ULUIInventory::ItemRemoved);
			}
		}
	}

	else
	{
		if (InventoryWidget->IsInViewport())
		{
			InventoryWidget->RemoveFromParent();
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());

			InventoryWidget->OnItemAdded.RemoveAll(InventoryWidget);
		}
		else
		{
			InventoryWidget->SetInventory(Inventory);
			InventoryWidget->SetMaxSize(MaxSize);
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI());
			InventoryWidget->AddToViewport();
				
			InventoryWidget->OnItemAdded.AddDynamic(InventoryWidget, &ULUIInventory::ItemAdded);
			InventoryWidget->OnItemDropped.AddDynamic(InventoryWidget, &ULUIInventory::ItemDropped);
			InventoryWidget->OnItemRemoved.AddDynamic(InventoryWidget, &ULUIInventory::ItemRemoved);
		}
	}
}

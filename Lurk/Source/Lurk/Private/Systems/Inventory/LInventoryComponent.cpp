// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Inventory/LInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/LItemDataAsset.h"
#include "Elements/Framework/TypedElementSelectionSet.h"
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

	DefaultInventoryState();
}

bool ULInventoryComponent::CheckRotation(float ItemRotation, ULItemComponent* ItemComponent)
{
	ULItemDataAsset* dataAsset = ItemComponent->GetDataAsset();

	FVector2D key;
	ItemComponent->SetRotation(ItemRotation);
	if (ShapeFits(dataAsset->GetShape(0.f), key))
	{
		AddToInventory(key, ItemComponent, true);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow, TEXT("CheckRotation true"));
		return true;
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow, TEXT("CheckRotation wrong"));
	return false;
}


void ULInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool ULInventoryComponent::PickUp(ULItemComponent* ItemToPickUp)
{
	if (CheckRotation(0.f, ItemToPickUp) ||
		CheckRotation(90.f, ItemToPickUp) ||
		CheckRotation(180.f, ItemToPickUp) ||
		CheckRotation(-90.f, ItemToPickUp))
	{
		return true;
	}

	else
	{
		return false;
	}
}

void ULInventoryComponent::AddToInventory(FVector2D SlotKey, ULItemComponent* SlotValue, bool bModifyState)
{
	Inventory.Add(SlotKey, SlotValue);

	if (bModifyState)
	{
		AddToState(SlotValue, SlotKey);
	}

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Purple,
	                                 FString::Printf(TEXT("ValidKey found: %s"), *SlotKey.ToString()));


	/*if (InventoryWidget)
	{
		InventoryWidget->OnItemAdded.Broadcast(SlotKey, SlotValue);
	}*/
}

void ULInventoryComponent::RemoveFromInventory(FVector2D SlotKey, bool bModifyState)
{
	if (bModifyState)
	{
		RemoveFromState(*Inventory.Find(SlotKey), SlotKey);
	}

	Inventory.Remove(SlotKey);

	/*if (InventoryWidget)
	{
		InventoryWidget->OnItemRemoved.Broadcast(SlotKey);
	}*/
}

void ULInventoryComponent::ItemDropped(ULItemDataAsset* ItemDropped)
{
	if (ALCharacter* CharacterOwner = GetOwner<ALCharacter>())
	{
		FVector ActorForwardVector = CharacterOwner->GetActorForwardVector();
		FVector ActorLocation = CharacterOwner->GetActorLocation();

		FVector Start = ActorForwardVector * 600.f + ActorLocation;
		FVector End = ActorForwardVector * 600.f + ActorLocation - FVector(0, 0, 500.f);

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
			GetWorld()->SpawnActor<ULItemComponent>(ItemDropped->GetClass(), HitResult.Location, FRotator::ZeroRotator,
			                                        SpawnParams);
		}
		DrawDebugBox(GetWorld(), HitResult.Location, BoxHalfSize, BoxRotation, FColor::Red, false, 5.0f);

		/*	if (InventoryWidget)
			{
				InventoryWidget->OnItemDropped.Broadcast(ItemDropped);
			}*/
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
				InventoryWidget->SetMaxSize(InventorySize);
				InventoryWidget->AddToViewport();

				/*InventoryWidget->OnItemAdded.AddDynamic(InventoryWidget, &ULUIInventory::ItemAdded);
				InventoryWidget->OnItemDropped.AddDynamic(InventoryWidget, &ULUIInventory::ItemDropped);
				InventoryWidget->OnItemRemoved.AddDynamic(InventoryWidget, &ULUIInventory::ItemRemoved);*/
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

			InventoryWidget = nullptr;
		}
		else
		{
			InventoryWidget->SetInventory(Inventory);
			InventoryWidget->SetMaxSize(InventorySize);
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI());
			InventoryWidget->AddToViewport();

			/*InventoryWidget->OnItemAdded.AddDynamic(InventoryWidget, &ULUIInventory::ItemAdded);
			InventoryWidget->OnItemDropped.AddDynamic(InventoryWidget, &ULUIInventory::ItemDropped);
			InventoryWidget->OnItemRemoved.AddDynamic(InventoryWidget, &ULUIInventory::ItemRemoved);*/
		}
	}
}

void ULInventoryComponent::DefaultInventoryState()
{
	float gridX = 0;
	float gridY = 0;

	for (int i = 0; i < InventorySize - 1; i++)
	{
		InventoryState.Add(FVector2D(gridX, gridY), false);

		if (gridX != InventoryWidth - 1)
		{
			gridX++;
		}
		else
		{
			gridX = 0;
			gridY++;
		}
	}

	TArray<FVector2D> keys;
	Inventory.GetKeys(keys);

	for (auto Key : keys)
	{
		AddToState(*Inventory.Find(Key), Key);
	}
}


void ULInventoryComponent::AddToState(ULItemComponent* ItemComponent, FVector2D Location)
{
	ULItemDataAsset* dataAsset = ItemComponent->GetDataAsset();
	TArray<FVector2D> itemShapes = dataAsset->GetShape(ItemComponent->GetRotation());

	for (auto shape : itemShapes)
	{
		InventoryState.Add(FVector2D(shape + Location), true);
	}
}

void ULInventoryComponent::RemoveFromState(ULItemComponent* ItemComponent, FVector2D Location)
{
	ULItemDataAsset* dataAsset = ItemComponent->GetDataAsset();
	TArray<FVector2D> itemShapes = dataAsset->GetShape(ItemComponent->GetRotation());

	for (auto shape : itemShapes)
	{
		InventoryState.Add(FVector2D(shape + Location), false);
	}
}

bool ULInventoryComponent::ShapeFits(TArray<FVector2D> Shape, FVector2D& ValidKey)
{
	TArray<FVector2D> keys;

	InventoryState.GetKeys(keys);

	for (auto Key : keys)
	{
		// Check if the current key is an empty slot
		if (!*InventoryState.Find(Key))
		{
			FVector2D emptySlot;
			emptySlot = Key;
			bool bFailed = false;

			// Check each item shape relative to the empty slot
			for (auto itemShape : Shape)
			{
				FVector2D currentPos = emptySlot + itemShape;

				if (!InventoryState.Find(currentPos))
				{
					bFailed = true;
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow,
					                                 FString::Printf(
						                                 TEXT("bFailed set to true at slot: %s"),
						                                 *currentPos.ToString()));
					break;
				}
				break;
			}

			// If bFailed is true, skip to the next key
			if (bFailed)
			{
				continue; // Continue to the next key
			}
			else
			{
				ValidKey = emptySlot;
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow,
				                                 FString::Printf(TEXT("ValidKey found: %s"), *ValidKey.ToString()));
				return true;
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Orange,
			                                 FString::Printf(TEXT("Slot %s is already occupied"), *Key.ToString()));
		}
	}
	return false;
}

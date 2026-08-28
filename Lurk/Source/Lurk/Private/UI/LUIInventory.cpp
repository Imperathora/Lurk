// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LUIInventory.h"
#include "Systems/Inventory/LInventoryComponent.h"

void ULUIInventory::ItemAdded(FVector2D Key, ULItemComponent* Item)
{
	Inventory.Add(Key, Item);

	if (IsValid(InventoryComponent))
	{
		InventoryComponent->AddToInventory(Key, Item, true);
	}
}

void ULUIInventory::ItemDropped(FVector2D Key)
{
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->ItemDropped(*Inventory.Find(Key));

		ItemRemoved(Key);
	}
}

void ULUIInventory::ItemRemoved(FVector2D Key)
{
	Inventory.Remove(Key);

	if (IsValid(InventoryComponent))
	{
		InventoryComponent->RemoveFromInventory(Key, true);
	}
}

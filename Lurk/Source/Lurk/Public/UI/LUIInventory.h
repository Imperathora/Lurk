// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LUIInventory.generated.h"

class ULInventoryComponent;
class ULItemDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, int32, ItemID, ULItemDataAsset*, ItemData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDropped, ULItemDataAsset*, ItemData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, int32, ItemID);

UCLASS()
class LURK_API ULUIInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetInventory(const TMap<FVector2D, ULItemComponent*>& inv) { Inventory = inv; }

	UFUNCTION(BlueprintCallable)
	void SetInventorySize(const int32 size) { InventorySize = size; }

	UFUNCTION(BlueprintCallable)
	void SetInventoryWidth(const int32 width) { InventoryWidth = width; }

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(ULInventoryComponent* inventoryComponent) { InventoryComponent = inventoryComponent; }

	UFUNCTION(BlueprintPure)
	int32 GetInventorySize() const { return InventorySize; }

	UFUNCTION(BlueprintPure)
	int32 GetInventoryWidth() const { return InventoryWidth; }

	UFUNCTION(BlueprintPure)
	TMap<FVector2D, ULItemComponent*> GetInventory() { return Inventory; }

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemDropped OnItemDropped;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemRemoved OnItemRemoved;

	UFUNCTION(BlueprintCallable)
	void ItemAdded(FVector2D Key, ULItemComponent* Item);

	UFUNCTION(BlueprintCallable)
	void ItemDropped(FVector2D Key);

	UFUNCTION(BlueprintCallable)
	void ItemRemoved(FVector2D Key);

private:
	UPROPERTY()
	TMap<FVector2D, ULItemComponent*> Inventory;

	UPROPERTY()
	int32 InventorySize;

	UPROPERTY()
	int32 InventoryWidth;

	UPROPERTY()
	ULInventoryComponent* InventoryComponent;
};

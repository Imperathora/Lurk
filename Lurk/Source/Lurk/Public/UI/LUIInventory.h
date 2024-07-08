// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LUIInventory.generated.h"

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
	void SetInventory(const TMap<FVector2D,ULItemComponent*>& inv) { Inventory = inv; }

	UFUNCTION(BlueprintCallable)
	void SetMaxSize(const int32 size) { WidgetSize = size; }

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemDropped OnItemDropped;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnItemRemoved OnItemRemoved;
	
	UFUNCTION(BlueprintCallable)
	void ItemAdded(int32 ItemID, ULItemDataAsset* ItemData);

	UFUNCTION(BlueprintCallable)
	void ItemDropped(ULItemDataAsset* ItemData);

	UFUNCTION(BlueprintCallable)
	void ItemRemoved(int32 ItemID);
	
	UPROPERTY(BlueprintReadWrite)
	TMap<FVector2D,ULItemComponent*> Inventory;

	UPROPERTY(BlueprintReadWrite)
	int32 WidgetSize;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LInventoryComponent.generated.h"

class ULItemComponent;
class ULUIInventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LURK_API ULInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULInventoryComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	bool PickUp (ULItemComponent* ItemToPickUp);

private:
	UFUNCTION(BlueprintPure)
	bool IsKeyFull (const int32& Key, int32& Remaining);

	UFUNCTION(BlueprintCallable)
	void ItemAdded (int32 SlotKey, ULItemDataAsset* SlotValue);

	UFUNCTION(BlueprintCallable)
	void ItemRemoved (int32 SlotKey);
	
	UFUNCTION(BlueprintCallable)
	void ItemDropped(ULItemDataAsset* ItemDropped);

	void OpenInventory();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TMap<int32,ULItemDataAsset*> Inventory;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxSize = 3;

	UPROPERTY()
	ULUIInventory* InventoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>  InventoryWidgetClass;
};

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
	UFUNCTION(BlueprintCallable)
	void AddToInventory (FVector2D SlotKey, ULItemComponent* SlotValue, bool bModifyState);

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory (FVector2D SlotKey, bool bModifyState);
	
	UFUNCTION(BlueprintCallable)
	void ItemDropped(ULItemDataAsset* ItemDropped);

	void OpenInventory();
	
	UFUNCTION(BlueprintCallable)
	void DefaultInventoryState ();

	UFUNCTION(BlueprintCallable)
	void AddToState (ULItemComponent* ItemComponent, FVector2D Location);

	UFUNCTION(BlueprintCallable)
	void RemoveFromState (ULItemComponent* ItemComponent, FVector2D Location);

	UFUNCTION(BlueprintCallable)
	bool ShapeFits (TArray<FVector2D> Shape, FVector2D& ValidKey);

protected:
	virtual void BeginPlay() override;

	bool CheckRotation(float ItemRotation, ULItemComponent* ItemComponent);

private:
	UPROPERTY(VisibleAnywhere)
	TMap<FVector2D,ULItemComponent*> Inventory;
	
	UPROPERTY(VisibleAnywhere)
	TMap<FVector2D,bool> InventoryState;

	UPROPERTY(EditDefaultsOnly)
	int32 InventorySize = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 InventoryWidth = 10;

	UPROPERTY()
	ULUIInventory* InventoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>  InventoryWidgetClass;
};

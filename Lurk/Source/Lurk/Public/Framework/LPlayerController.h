// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"


class ULInventoryGrid;
class ULInventoryWidget;

UCLASS()
class LURK_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void OpenInventory();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(ULItemComponent* Item);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget>  InventoryWidgetClass;

protected:
	virtual void BeginPlay() override;
	void InitializeInventoryGrid();

private:
	UPROPERTY()
	ULInventoryGrid* InventoryGrid;

	UPROPERTY()
	ULInventoryWidget* InventoryWidget;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LInventoryWidget.generated.h"

class ULInventoryGrid;

UCLASS()
class LURK_API ULInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void InitializeInventory(ULInventoryGrid* Inventory);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UpdateInventoryUI();

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UUniformGridPanel* InventoryGridPanel;

private:
    UPROPERTY()
    ULInventoryGrid* InventoryGrid;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LInventoryWidget.generated.h"

class ULInventoryGrid;
class ULItemComponent;
class ULItemViewerWidget;
class ULInventoryItemWidget;

UCLASS()
class LURK_API ULInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void InitializeInventory(ULInventoryGrid* Inventory);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UpdateInventoryUI();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void OnItemRightClicked(ULItemComponent* Item);

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UUniformGridPanel* InventoryGridPanel;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ItemWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ItemViewerWidgetClass;

private:
    UPROPERTY()
    ULInventoryGrid* InventoryGrid;

    UPROPERTY()
    ULItemViewerWidget* ItemViewerWidget;
};

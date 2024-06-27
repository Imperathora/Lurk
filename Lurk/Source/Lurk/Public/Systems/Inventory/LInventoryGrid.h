// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LInventoryGrid.generated.h"

class ULItemComponent;

UCLASS(Blueprintable, BlueprintType)
class LURK_API ULInventoryGrid : public UObject
{
	GENERATED_BODY()
	
public:
    ULInventoryGrid();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    int32 Rows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    int32 Columns;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
    TArray<ULItemComponent*> Items;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(ULItemComponent* NewItem, int32 StartRow, int32 StartColumn);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(ULItemComponent* Item);

private:
    TArray<TArray<ULItemComponent*>> Grid;

    bool IsSpaceAvailable(ULItemComponent* Item, int32 StartRow, int32 StartColumn);
    void PlaceItem(ULItemComponent* Item, int32 StartRow, int32 StartColumn);
    void ClearItem(ULItemComponent* Item);
};

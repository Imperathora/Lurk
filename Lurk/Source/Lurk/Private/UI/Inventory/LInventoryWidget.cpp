// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LInventoryWidget.h"
#include "Systems/Inventory/LInventoryGrid.h"

#include "Systems/Interaction/LItemComponent.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"

void ULInventoryWidget::InitializeInventory(ULInventoryGrid* Inventory)
{
    InventoryGrid = Inventory;
    UpdateInventoryUI();
}

void ULInventoryWidget::UpdateInventoryUI()
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateInventoryUI called"));

    if (!InventoryGrid || !InventoryGridPanel)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryGrid or InventoryGridPanel is null"));
        return;
    }

    InventoryGridPanel->ClearChildren();

    for (ULItemComponent* Item : InventoryGrid->Items)
    {
        if (Item)
        {
            UTextBlock* ItemText = NewObject<UTextBlock>(InventoryGridPanel);
            ItemText->SetText(FText::FromString(Item->ItemName));

            // Find the item's position in the grid
            int32 StartRow = -1;
            int32 StartColumn = -1;

            for (int32 Row = 0; Row < InventoryGrid->Rows; ++Row)
            {
                for (int32 Column = 0; Column < InventoryGrid->Columns; ++Column)
                {
                    if (InventoryGrid->Grid[Row][Column] == Item)
                    {
                        StartRow = Row;
                        StartColumn = Column;
                        break;
                    }
                }
                if (StartRow != -1) break;
            }

            if (StartRow != -1 && StartColumn != -1)
            {
                UE_LOG(LogTemp, Warning, TEXT("Placing item %s at Row: %d, Column: %d"), *Item->ItemName, StartRow, StartColumn);
                UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(ItemText);
                GridSlot->SetRow(StartRow);
                GridSlot->SetColumn(StartColumn);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Could not find position for item %s"), *Item->ItemName);
            }
        }
    }

    InventoryGridPanel->InvalidateLayoutAndVolatility();
}
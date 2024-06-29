// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LInventoryWidget.h"
#include "Systems/Inventory/LInventoryGrid.h"

#include "Systems/Interaction/LItemComponent.h"

#include "UI/Inventory/LItemViewerWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/LInventoryItemWidget.h"

void ULInventoryWidget::InitializeInventory(ULInventoryGrid* Inventory)
{
    InventoryGrid = Inventory;
    UpdateInventoryUI();
}

void ULInventoryWidget::UpdateInventoryUI()
{
    if (!InventoryGrid || !InventoryGridPanel) return;

    InventoryGridPanel->ClearChildren();

    for (ULItemComponent* Item : InventoryGrid->Items)
    {
        if (Item)
        {
            ULInventoryItemWidget* ItemWidget = CreateWidget<ULInventoryItemWidget>(this, ItemWidgetClass);
            ItemWidget->SetItem(Item);
            ItemWidget->OnItemRightClicked.AddDynamic(this, &ULInventoryWidget::OnItemRightClicked);

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
                UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(ItemWidget);
                GridSlot->SetRow(StartRow);
                GridSlot->SetColumn(StartColumn);
            }
        }
    }

    InventoryGridPanel->InvalidateLayoutAndVolatility();
}

void ULInventoryWidget::OnItemRightClicked(ULItemComponent* Item)
{
    if (!ItemViewerWidget)
    {
        ItemViewerWidget = CreateWidget<ULItemViewerWidget>(this, ItemViewerWidgetClass);
        if (ItemViewerWidget)
        {
            ItemViewerWidget->AddToViewport();
        }
    }

    if (ItemViewerWidget)
    {
        ItemViewerWidget->SetItem(Item);
        ItemViewerWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

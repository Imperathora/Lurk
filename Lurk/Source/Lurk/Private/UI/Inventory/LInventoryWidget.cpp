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
    if (!InventoryGrid) return;

    UUniformGridPanel* GridPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("InventoryGridPanel")));
    if (!GridPanel) return;

    GridPanel->ClearChildren();

    for (ULItemComponent* Item : InventoryGrid->Items)
    {
        if (Item)
        {
            UTextBlock* ItemText = NewObject<UTextBlock>(GridPanel);
            ItemText->SetText(FText::FromString(Item->ItemName));

            UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(ItemText);
            GridSlot->SetRow(Item->GetOwner()->GetActorLocation().X);  // Adjust this as necessary
            GridSlot->SetColumn(Item->GetOwner()->GetActorLocation().Y);  // Adjust this as necessary
        }
    }
}
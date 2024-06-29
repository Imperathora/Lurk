// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LInventoryItemWidget.h"

#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Systems/Interaction/LItemComponent.h"

FReply ULInventoryItemWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        OnItemRightClicked.Broadcast(Item);
        return FReply::Handled();
    }

    return FReply::Unhandled();
}

void ULInventoryItemWidget::SetItem(ULItemComponent* NewItem)
{
    Item = NewItem;
    if (Item && ItemNameText)
    {
        ItemNameText->SetText(FText::FromString(Item->ItemName));
    }
}

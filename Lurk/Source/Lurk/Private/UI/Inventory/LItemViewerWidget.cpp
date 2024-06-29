// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Inventory/LItemViewerWidget.h"
#include "Systems/Interaction/LItemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextBlock.h"
#include "Engine/StaticMesh.h"
#include "Components/WidgetComponent.h"

void ULItemViewerWidget::SetItem(ULItemComponent* NewItem)
{
   /* Item = NewItem;
    if (Item && Item->GetItemMesh())
    {
        ItemMeshComponent->SetStaticMesh(Item->GetItemMesh());
    }*/
    Item = NewItem;
    if (Item)
    {
        // Update item details in the UI
        ItemNameText->SetText(FText::FromString(Item->ItemName));
    }
}

void ULItemViewerWidget::NativeConstruct()
{
    Super::NativeConstruct();

    /*ViewerRoot = NewObject<USceneComponent>(this);
    ViewerRoot->RegisterComponent();

    ItemMeshComponent = NewObject<UStaticMeshComponent>(this);
    ItemMeshComponent->AttachToComponent(ViewerRoot, FAttachmentTransformRules::KeepRelativeTransform);
    ItemMeshComponent->RegisterComponent();

  /*  if (!ItemViewer)
    {
        ItemViewer = NewObject<UWidgetComponent>(this, TEXT("ItemViewer"));
        ItemViewer->AttachToComponent(ViewerRoot, FAttachmentTransformRules::KeepRelativeTransform);
        ItemViewer->RegisterComponent();
    }*/
}

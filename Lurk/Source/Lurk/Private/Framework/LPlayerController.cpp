// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/LPlayerController.h"

#include "UI/Inventory/LInventoryWidget.h"
#include "Systems/Inventory/LInventoryGrid.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ALPlayerController::ALPlayerController()
{
    InventoryGrid = NewObject<ULInventoryGrid>();
    InventoryGrid->Rows = 10; // Example initialization
    InventoryGrid->Columns = 10; // Example initialization
}

void ALPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("OpenInventory", IE_Pressed, this, &ALPlayerController::OpenInventory);
}


void ALPlayerController::OpenInventory()
{
    if (!InventoryWidget)
    {
        InventoryWidget = CreateWidget<ULInventoryWidget>(this, InventoryWidgetClass);
            if (InventoryWidget)
            {
                InventoryWidget->AddToViewport();
                InventoryWidget->InitializeInventory(InventoryGrid);
                bShowMouseCursor = true;
                SetInputMode(FInputModeUIOnly());
            }
    }
    else if (InventoryWidget->IsInViewport())
    {
        InventoryWidget->RemoveFromParent();
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }
}
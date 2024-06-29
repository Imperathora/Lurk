// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/LPlayerController.h"

#include "UI/Inventory/LInventoryWidget.h"
#include "Systems/Inventory/LInventoryGrid.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include <Systems/LCharacter.h>

void ALPlayerController::OpenInventory()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Yellow, TEXT("open inventory PC"));
	if (!InventoryWidget)
	{
		if (InventoryWidgetClass)
		{

			InventoryWidget = CreateWidget<ULInventoryWidget>(this, InventoryWidgetClass);
			if (InventoryWidget)
			{
				InventoryWidget->AddToViewport();
				InventoryWidget->InitializeInventory(InventoryGrid);
				InventoryWidget->UpdateInventoryUI();
				bShowMouseCursor = true;
				//SetInputMode(FInputModeUIOnly());
			}
		}
	}

	else
	{
		if (InventoryWidget->IsInViewport())
		{
			InventoryWidget->RemoveFromParent();
			bShowMouseCursor = false;
			//SetInputMode(FInputModeGameOnly());
		}
		else
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->InitializeInventory(InventoryGrid);
			InventoryWidget->UpdateInventoryUI(); // Ensure UI is updated
			bShowMouseCursor = true;
			//SetInputMode(FInputModeUIOnly());
		}
	}
}

void ALPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeInventoryGrid();
}

void ALPlayerController::InitializeInventoryGrid()
{
	InventoryGrid = NewObject<ULInventoryGrid>(this);
	InventoryGrid->Rows = 10; 
	InventoryGrid->Columns = 10; 

	UE_LOG(LogTemp, Warning, TEXT("InventoryGrid initialized with %d rows and %d columns"), InventoryGrid->Rows, InventoryGrid->Columns);
}


void ALPlayerController::AddItemToInventory(ULItemComponent* Item)
{
	if (InventoryGrid && InventoryGrid->AddItemToFirstFreeSpace(Item))
	{
		if (InventoryWidget)
		{
			InventoryWidget->UpdateInventoryUI();
		}
	}
}
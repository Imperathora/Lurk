// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Inventory/LInventoryGrid.h"
#include "Systems/Interaction/LItemComponent.h"

ULInventoryGrid::ULInventoryGrid()
{
    Rows = 10; 
    Columns = 10; 
    Grid.SetNum(Rows);

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        Grid[Row].SetNum(Columns);
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            Grid[Row][Column] = nullptr;
        }
    }
}

bool ULInventoryGrid::AddItem(ULItemComponent* NewItem, int32 StartRow, int32 StartColumn)
{
    if (IsSpaceAvailable(NewItem, StartRow, StartColumn))
    {
        PlaceItem(NewItem, StartRow, StartColumn);
        Items.Add(NewItem);
        return true;
    }
    return false;
}

bool ULInventoryGrid::RemoveItem(ULItemComponent* Item)
{
    if (Items.Contains(Item))
    {
        ClearItem(Item);
        Items.Remove(Item);
        return true;
    }
    return false;
}

bool ULInventoryGrid::AddItemToFirstFreeSpace(ULItemComponent* NewItem)
{
    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            if (IsSpaceAvailable(NewItem, Row, Column))
            {
                PlaceItem(NewItem, Row, Column);
                Items.Add(NewItem);
                UE_LOG(LogTemp, Warning, TEXT("Placed item at Row: %d, Column: %d"), Row, Column);
                return true;
            }
        }
    }
    return false; // No space available
}

bool ULInventoryGrid::IsSpaceAvailable(ULItemComponent* Item, int32 StartRow, int32 StartColumn)
{
    if (StartRow + Item->GetItemInventoryHeight() > Rows || StartColumn + Item->GetItemInventoryWidth() > Columns)
    {
        return false;
    }

    for (int32 Row = StartRow; Row < StartRow + Item->GetItemInventoryHeight(); ++Row)
    {
        for (int32 Column = StartColumn; Column < StartColumn + Item->GetItemInventoryWidth(); ++Column)
        {
            if (Grid[Row][Column] != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

void ULInventoryGrid::PlaceItem(ULItemComponent* Item, int32 StartRow, int32 StartColumn)
{
    for (int32 Row = StartRow; Row < StartRow + Item->GetItemInventoryHeight(); ++Row)
    {
        for (int32 Column = StartColumn; Column < StartColumn + Item->GetItemInventoryWidth(); ++Column)
        {
            Grid[Row][Column] = Item;
        }
    }
}

void ULInventoryGrid::ClearItem(ULItemComponent* Item)
{
    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            Grid[Row][Column] = Item;
        }
    }
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/LItemDataAsset.h"

TArray<FVector2D> ULItemDataAsset::GetShape(float rotation)
{
	if (rotation == 0)
	{
		return DefaultItemShape;
	}

	else
	{
		TArray<FVector2D> returnShape;
		float smallestX = 0;
		float smallestY = 0;
		for (auto shape : DefaultItemShape)
		{
			returnShape.Add(shape.GetRotated(rotation));

			if (smallestX > shape.X)
			{
				smallestX = shape.X;
			}
			else if (smallestY > shape.Y)
			{
				smallestY = shape.Y;
			}
		}

		for (int i = 0; i < returnShape.Num(); i++)
		{
			returnShape[i] = returnShape[i] - FVector2D(smallestX, smallestY);
		}

		return returnShape;
	}
}

void ULItemDataAsset::DetermineShape(UPaperTileMapComponent* tilemapComponent)
{
	DefaultItemShape.Empty();
	int32 mapWidth;
	int32 mapHeight;
	int32 numLayers;
	
	tilemapComponent->GetMapSize(mapWidth, mapHeight, numLayers);

	for(int i = 0; i < mapWidth-1; i++)
	{
		int32 mapX = i;
		for(int j = 0; j < mapHeight-1; j++)
		{
			int32 mapY = j;

			if(tilemapComponent->GetTile(mapX,mapY,GetLayer()).TileSet == TileSet)
			{
				DefaultItemShape.Add(FVector2D(mapX,mapY));
			}
		}
	}
}

FVector2D ULItemDataAsset::GetMaxSize(float rotation, bool defaultOverride)
{
	TArray<FVector2D> tempShape;
	float maxX = 0;
	float maxY = 0;
	if (defaultOverride)
	{
		tempShape = DefaultItemShape;
	}
	else
	{
		tempShape = GetShape(rotation);
	}
	
	for (auto shape : tempShape)
	{
		if (maxX > shape.X)
		{
			maxX = shape.X;
		}
		else if (maxY > shape.Y)
		{
			maxY = shape.Y;
		}
	}
	return FVector2D(maxX,maxY);
}

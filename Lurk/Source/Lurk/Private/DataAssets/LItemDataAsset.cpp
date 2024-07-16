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

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Green,
	                                 FString::Printf(
		                                 TEXT("Map Size - Width: %d, Height: %d, Layers: %d"), mapWidth, mapHeight,
		                                 numLayers));

	for (int i = 0; i <= mapWidth - 1; i++)
	{
		int32 mapX = i;
		for (int j = 0; j <= mapHeight - 1; j++)
		{
			int32 mapY = j;
			if (numLayers > 0)
			{
				FPaperTileInfo tileInfo = tilemapComponent->GetTile(mapX, mapY, GetLayer());
				TObjectPtr<UPaperTileSet> tileSet = tileInfo.TileSet;

				if (tileSet)
				{
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Purple,
					                                 FString::Printf(
						                                 TEXT("Tile found: %s"), *tileSet.GetFName().ToString()));
					if (tileSet == TileSet)
					{
						DefaultItemShape.Add(FVector2D(mapX, mapY));
					}
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Red,
					                                 FString::Printf(TEXT("Tile at (%d, %d) is null"), mapX, mapY));
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Red,
				                                 FString::Printf(TEXT("No layers available in the tilemap")));
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
		if (maxX < shape.X)
		{
			maxX = shape.X;
		}
		if (maxY < 0)
		{
			maxY = shape.Y;
		}
	}
	return FVector2D(maxX + 1.f, maxY + 1.f);
}

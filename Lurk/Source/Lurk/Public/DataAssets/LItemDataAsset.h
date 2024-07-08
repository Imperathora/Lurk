// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Paper2D/Classes/PaperTileMapComponent.h"
#include "LItemDataAsset.generated.h"


UENUM()
enum class EItemType : uint8
{
	Carriable,
	Inspectable
};

UCLASS()
class LURK_API ULItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintCallable)
	FText GetItemName() const { return ItemName; }

	UFUNCTION(BlueprintCallable)
	int32 GetLayer() const { return ItemLayer; }

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetItemTexture() const { return ItemTexture; }

	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> GetShape(float rotation);

	UFUNCTION(BlueprintCallable)
	void DetermineShape(UPaperTileMapComponent* tilemapComponent);

	UFUNCTION(BlueprintCallable)
	FVector2D GetMaxSize(float rotation, bool defaultOverride);

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = "Item")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* ItemTexture;

	UPROPERTY(EditAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item")
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 ItemLayer;

	UPROPERTY(EditAnywhere, Category = "Item")
	TArray<FVector2D> DefaultItemShape;

	UPROPERTY(EditAnywhere, Category = "Item")
	UPaperTileSet* TileSet;
};

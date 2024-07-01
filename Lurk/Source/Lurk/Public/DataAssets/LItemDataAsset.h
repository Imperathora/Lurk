// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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
	FText GetDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintCallable)
	FText GetName() const { return ItemName; }

	UFUNCTION(BlueprintCallable)
	int32 GetWidth() const { return ItemWidth; }

	UFUNCTION(BlueprintCallable)
	int32 GetHeight() const { return ItemHeight; }

	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetMesh() const { return ItemMesh; }

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = "Item")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* ItemMesh;

	UPROPERTY(EditAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item")
	class USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 ItemWidth = 1;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 ItemHeight = 1;
};

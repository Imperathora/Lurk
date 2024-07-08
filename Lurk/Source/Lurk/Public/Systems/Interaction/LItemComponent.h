// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LItemComponent.generated.h"

class ULItemDataAsset;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LURK_API ULItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULItemComponent();

	UFUNCTION(BlueprintCallable)
	FText GetInteractionText() const;

	UFUNCTION(BlueprintCallable)
	ULItemDataAsset* GetDataAsset() const { return ItemData; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;

	UFUNCTION(BlueprintCallable)
	float GetRotation() const { return Rotation; }

	UFUNCTION(BlueprintCallable)
	void SetRotation(float rotation) {  Rotation = rotation; }

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	void ItemInteraction();

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	ULItemDataAsset* ItemData;

	UPROPERTY(EditAnywhere, Category = "Item")
	float Rotation;
};

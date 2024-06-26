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

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	FText GetInteractionText() const;

	void ItemInteraction();

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	ULItemDataAsset* ItemData;
};

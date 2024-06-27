// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"


class ULInventoryGrid;
class ULInventoryWidget;

UCLASS()
class LURK_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ALPlayerController();

protected:
    virtual void SetupInputComponent() override;

private:
    UPROPERTY()
    ULInventoryGrid* InventoryGrid;

    UPROPERTY()
    ULInventoryWidget* InventoryWidget;

    void OpenInventory();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget>  InventoryWidgetClass;
};

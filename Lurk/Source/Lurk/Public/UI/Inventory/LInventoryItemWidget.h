// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LInventoryItemWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRightClicked, class ULItemComponent*, Item);

class ULItemComponent;

UCLASS()
class LURK_API ULInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemNameText;

    UPROPERTY(BlueprintReadOnly)
    class ULItemComponent* Item;

    UPROPERTY(BlueprintAssignable)
    FOnItemRightClicked OnItemRightClicked;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
    void SetItem(class ULItemComponent* NewItem);
};

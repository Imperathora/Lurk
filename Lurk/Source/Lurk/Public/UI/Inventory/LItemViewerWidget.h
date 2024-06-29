// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LItemViewerWidget.generated.h"

class ULItemComponent;

UCLASS()
class LURK_API ULItemViewerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetItem(ULItemComponent* NewItem);

    virtual void NativeConstruct() override;

private:
    class USceneComponent* ViewerRoot;
    class UStaticMeshComponent* ItemMeshComponent;

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UOverlay* OverlayWidget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UTextBlock* ItemNameText;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UImage* ItemImage;

    UPROPERTY(BlueprintReadOnly)
    ULItemComponent* Item;
};

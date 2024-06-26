// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "LInteractionWidget.generated.h"

class UTextBlock;


UCLASS()
class LURK_API ULInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Text Block")
	TObjectPtr<UTextBlock> InteractionText;

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	FText GetInteractionText();
};

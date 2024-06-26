// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "LPlayerHud.generated.h"

class ULInteractionWidget;
/**
 * 
 */
UCLASS()
class LURK_API ALPlayerHud : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULInteractionWidget> InteractionPrompt;

private:
	virtual void BeginPlay() override;
};

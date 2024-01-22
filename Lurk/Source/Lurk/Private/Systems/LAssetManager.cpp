// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/LAssetManager.h"
#include "AbilitySystemGlobals.h"

void ULAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

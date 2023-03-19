// Fill out your copyright notice in the Description page of Project Settings.


#include "LAssetManager.h"
#include "AbilitySystemGlobals.h"

void ULAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LInteractionComponent.generated.h"

using FOnInteractDelegate = TDelegate<void()>;
using FCanInteractDelegate = TDelegate<bool()>;

//Allows owning actor to recieve interaction event from player

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LURK_API ULInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnInteractDelegate OnInteract;

	FCanInteractDelegate CanInteract;

	bool TryInteract();
};

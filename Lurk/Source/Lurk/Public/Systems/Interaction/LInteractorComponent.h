// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LInteractorComponent.generated.h"

class ULInteractableComponent;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LURK_API ULInteractorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	ULInteractorComponent();

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	void UpdateInteractionCandidates();
	void PerformInteraction();

	UPROPERTY(EditDefaultsOnly)
	float InteractionDistance = 500.f;

	UPROPERTY(EditDefaultsOnly)
	float InteractionCircumference = 20.f;

	UPROPERTY(Transient)
	TObjectPtr<ULInteractableComponent> InteractionTarget = nullptr;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LDoorComponent.generated.h"

UENUM()
enum class EDoorState : uint8
{
	Opened,
	Closed,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LURK_API ULDoorComponent : public UActorComponent
{
	GENERATED_BODY()
	
	public:
		ULDoorComponent();

	private:
		virtual void BeginPlay() override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

		void OnDoorInteraction();
		FQuat GetTargetRotation() const;

	public:
		UPROPERTY(EditAnywhere)
		FVector OpenDelta = FVector(0.0, 0.0, 90.0);

		UPROPERTY(EditAnywhere)
		float OpenSpeed = 3.0f;

	private:
		FQuat InitialRotation;

		EDoorState TargetState = EDoorState::Closed;
};


// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Interaction/LInteractorComponent.h"

#include <Kismet/KismetSystemLibrary.h>

#include "Systems/LCharacter.h"
#include "Systems/Interaction/LInteractableComponent.h"


ULInteractorComponent::ULInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ALCharacter* CharacterOwner = GetOwner<ALCharacter>())
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(CharacterOwner->InputComponent);

		EnhancedInputComponent->BindAction(CharacterOwner->GetInteractAction(), ETriggerEvent::Triggered, this, &ULInteractorComponent::PerformInteraction);
	}
}

void ULInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateInteractionCandidates();
}

void ULInteractorComponent::UpdateInteractionCandidates()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(ULInteractorComponent::UpdateInteractionCandidates);

	const APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	const FVector CameraLocation = CameraManager->GetCameraLocation();
	const FVector CameraForward = CameraManager->GetCameraRotation().Vector();

	const FVector Start = CameraLocation;
	const FVector End = Start + CameraForward * InteractionDistance;
	const float Radius = InteractionCircumference;
	const float HalfHeight = InteractionCircumference;

	const bool bTraceComplex = false;
	const bool bIgnoreSelf = true;

	const TArray<AActor*> ActorsToIgnore;
	
	const ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	const EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForOneFrame;
	const FLinearColor TraceColor = FLinearColor(FColorList::Orange);
	const FLinearColor TraceHitColor = FLinearColor(FColorList::Red);

	TArray<FHitResult> OutHits;
	UKismetSystemLibrary::CapsuleTraceMulti(this, Start, End, Radius, HalfHeight, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor);


	TArray<ULInteractableComponent*> CandidateInteractables;

	FString DebugState = TEXT("Current Candidates: \n");

	for (const FHitResult& Hit : OutHits)
	{
		const AActor* HitActor = Hit.GetActor();
		ULInteractableComponent* HitInteractable = HitActor ? HitActor->FindComponentByClass<ULInteractableComponent>() : nullptr;
		if (HitInteractable)
		{
			CandidateInteractables.Add(HitInteractable);
			DebugState.Appendf(TEXT(" % s\n"), *HitActor->GetHumanReadableName());
		}

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Red, DebugState);
	}

	if (!CandidateInteractables.IsEmpty())
	{
		InteractionTarget = CandidateInteractables[0];
	}
	else
	{
		InteractionTarget = nullptr;
	}

}

void ULInteractorComponent::PerformInteraction()
{
	if (InteractionTarget)
	{
		InteractionTarget->TryInteract();
	}
}


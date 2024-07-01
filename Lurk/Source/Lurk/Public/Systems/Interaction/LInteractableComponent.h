#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LInteractableComponent.generated.h"

using FOnInteractDelegate = TDelegate<void()>;
using FCanInteractDelegate = TDelegate<bool()>;
using FGetInteractTextDelegate = TDelegate<FText()>;

//Allows owning actor to receive interaction event from player

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LURK_API ULInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnInteractDelegate OnInteract;

	FCanInteractDelegate CanInteract;

	FGetInteractTextDelegate GetInteractText;

	bool TryInteract();

	FText  GetInteractionText() const;
};

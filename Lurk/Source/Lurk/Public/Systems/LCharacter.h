#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "LCharacter.generated.h"
class ULInventoryGrid;
class ULInventoryWidget;
class ULItemComponent;

UCLASS()
class LURK_API ALCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALCharacter();

	virtual void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UInputAction* GetInteractAction();
	UInputAction* GetOpenInventoryAction();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_Interact;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* Input_OpenInventory;
};

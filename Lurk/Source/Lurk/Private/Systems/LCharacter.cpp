#include "Systems/LCharacter.h"

#include "UI/Inventory/LInventoryWidget.h"
#include "Systems/Inventory/LInventoryGrid.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Systems/Interaction/LItemComponent.h"

#include "Framework/LPlayerController.h"

// Sets default values
ALCharacter::ALCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultInputMapping, 0);
		}
	}
}


void ALCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	EnhancedInputSubsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(this->InputComponent);

	EnhancedInputComponent->BindAction(GetOpenInventoryAction(), ETriggerEvent::Triggered, this, &ALCharacter::OpenInventory);
}

UInputAction* ALCharacter::GetInteractAction()
{
	return Input_Interact;
}

UInputAction* ALCharacter::GetOpenInventoryAction()
{
	return Input_OpenInventory;
}

void ALCharacter::OpenInventory()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.f, FColor::Blue, TEXT("open inventory"));

	ALPlayerController* PlayerController = Cast<ALPlayerController>(GetController());
	PlayerController->OpenInventory();
}

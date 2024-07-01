#include "Systems/LCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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
}

UInputAction* ALCharacter::GetInteractAction()
{
	return Input_Interact;
}

UInputAction* ALCharacter::GetOpenInventoryAction()
{
	return Input_OpenInventory;
}
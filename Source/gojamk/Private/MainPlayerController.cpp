


#include "gojamk/Public/MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "gojamk/Public/JoseMorinho.h"

void AMainPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	
	player = Cast<AJoseMorinho>(aPawn);
	if (!player){return;}

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent){return;}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!EnhancedInputSubsystem){return;}

	EnhancedInputSubsystem->ClearAllMappings();
	EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext,0);

	EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayerController::Look);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainPlayerController::HandleJump);
}

void AMainPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (!player->Controller)
	{
		return;
	}
	const FRotator Rotation = player->Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	player->AddMovementInput(ForwardDirection, MovementVector.Y);
	player->AddMovementInput(RightDirection, MovementVector.X);
}

void AMainPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2d lookVector = Value.Get<FVector2D>();
	if (!player){return;}
	AddYawInput(lookVector.X);
	AddPitchInput(lookVector.Y);
}

void AMainPlayerController::HandleJump()
{
	if (!player){return;}
	player->UnCrouch();
	player->Jump();
}


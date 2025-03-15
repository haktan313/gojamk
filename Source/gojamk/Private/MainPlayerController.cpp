


#include "gojamk/Public/MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Enemys/EnemyBase.h"
#include "gojamk/Public/JoseMorinho.h"
#include "Kismet/KismetSystemLibrary.h"

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
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainPlayerController::AttackWithHammer);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AMainPlayerController::Dash);
}

void AMainPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMainPlayerController::Move(const FInputActionInstance& Value)
{
	FVector2D MovementVector = Value.GetValue().Get<FVector2d>(); 
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

void AMainPlayerController::AttackWithHammer()
{
	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hits;
	ignoreActors.Add(player);
	FVector end = player->GetActorLocation() + player->GetActorForwardVector() * 300;
	bool bHit = UKismetSystemLibrary::SphereTraceMulti(
		player->GetWorld(),
		player->GetActorLocation(),
		end,
		36 ,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false,
		ignoreActors,
		EDrawDebugTrace::ForDuration,
		hits,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5
		);
	if (bHit)
	{
		for (const FHitResult& hit : hits)
		{
			AEnemyBase* enemy = Cast<AEnemyBase>(hit.GetActor());
			if (enemy)
			{
				FS_DamageInfo damageInfo;
				damageInfo.AmountOfDamage = 10;
				damageInfo.DamageReactionAnimation = nullptr;
				damageInfo.DeathReactionAnimation = nullptr;
				player->HStatHandler->DamageTo(damageInfo,enemy);
			}
		}
	}
}

void AMainPlayerController::Dash()
{
	
}



#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "MainPlayerController.generated.h"


UCLASS()
class GOJAMK_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void Move(const FInputActionInstance& Value);
	void Look(const FInputActionValue& Value);
	void HandleJump();

	void AttackWithHammer();

	void Dash();

	TObjectPtr<class AJoseMorinho> player;
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

	FVector2d MovementVector;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<class UInputAction> MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Animations")
	TObjectPtr<UAnimMontage> DashForwardAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Animations")
	TObjectPtr<UAnimMontage> DashBackwardAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Animations")
	TObjectPtr<UAnimMontage> DashLeftAnimation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Animations")
	TObjectPtr<UAnimMontage> DashRightAnimation;
	UPROPERTY()
	TObjectPtr<UAnimMontage> dashAnimation;

	
};

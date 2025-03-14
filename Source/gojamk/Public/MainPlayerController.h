
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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void HandleJump();

	TObjectPtr<class AJoseMorinho> player;
	TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<class UInputAction> MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input|Movement")
	TObjectPtr<UInputAction> JumpAction;
};

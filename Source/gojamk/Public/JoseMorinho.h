

#pragma once

#include "CoreMinimal.h"
#include "HStatHandler.h"
#include "HTokenSystemComponent.h"
#include "GameFramework/Character.h"
#include "JoseMorinho.generated.h"

UCLASS()
class GOJAMK_API AJoseMorinho : public ACharacter
{
	GENERATED_BODY()

	UFUNCTION()
	void OnDeath(UAnimMontage* DeathAnimation);
	AJoseMorinho();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	TObjectPtr<class UAnimInstance> AnimInstancePlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHTokenSystemComponent> HTokenSystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHStatHandler> HStatHandler;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	//TSubclassOf<class UUserWidget> BaseStatWidgetClass;
	
};

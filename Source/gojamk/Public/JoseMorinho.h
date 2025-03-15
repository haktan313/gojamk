

#pragma once

#include "CoreMinimal.h"
#include "HTokenSystemComponent.h"
#include "GameFramework/Character.h"
#include "JoseMorinho.generated.h"

UCLASS()
class GOJAMK_API AJoseMorinho : public ACharacter
{
	GENERATED_BODY()
	
	AJoseMorinho();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHTokenSystemComponent> HTokenSystemComponent;
	
};

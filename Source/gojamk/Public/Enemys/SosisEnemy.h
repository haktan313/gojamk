
#pragma once

#include "CoreMinimal.h"
#include "Enemys/EnemyBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SosisEnemy.generated.h"


UCLASS()
class GOJAMK_API ASosisEnemy : public AEnemyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	ASosisEnemy();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DoAction(int ActionID);

	void ThrowSosis();
	
};

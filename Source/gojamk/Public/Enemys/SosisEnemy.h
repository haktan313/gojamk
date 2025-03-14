

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SosisEnemy.generated.h"


UCLASS()
class GOJAMK_API ASosisEnemy : public AEnemyBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	ASosisEnemy();
	
	void BeginPlay() override;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnDoAction(int ActionID);

	void ThrowSosis();
	
};

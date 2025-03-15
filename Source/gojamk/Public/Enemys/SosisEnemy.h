
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	float BounceForce = 1000;

	ASosisEnemy();

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	FTimerHandle bouncedEndTimer;
	void BouncedEnd();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void DoAction(int ActionID);

	void ThrowSosis();
	
};

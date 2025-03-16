
#pragma once

#include "CoreMinimal.h"
#include "HAIBaseComponent.h"
#include "HStatHandler.h"
#include "HTokenSystemComponent.h"
#include "SpitForPickle.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GOJAMK_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UHAIBaseComponent> HAIBaseComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UHTokenSystemComponent> HTokenSystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UHStatHandler> HStatHandler;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	float BounceForce = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TSubclassOf<ASpitForPickle> SpitForPickleClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TSubclassOf<AEnemyBase> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	FString enemyLootType;
	
	AEnemyBase();

	AActor* GetTargetActor();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnDeath(UAnimMontage* DeathAnimation);
	UFUNCTION()
	void OnDamageResponse(UAnimMontage* DamageAnimation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	float throwselfDamage = 1;
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	FTimerHandle bouncedEndTimer;
	void BouncedEnd();
	UFUNCTION()
	void DoAction(int ActionID);
	void ThrowSosis();
	FTimerHandle spitTimer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	float perSecondForSpit = 1;
	void Spit();

	void SplitPickle();

};

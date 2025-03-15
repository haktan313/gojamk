
#pragma once

#include "CoreMinimal.h"
#include "HAIBaseComponent.h"
#include "HTokenSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class GOJAMK_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UCapsuleComponent> Capsule;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<USkeletalMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UHAIBaseComponent> HAIBaseComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<UHTokenSystemComponent> HTokenSystemComponent;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	float BounceForce = 1000;
	
	AEnemyBase();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	FTimerHandle bouncedEndTimer;
	void BouncedEnd();
	UFUNCTION()
	void DoAction(int ActionID);
	void ThrowSosis();

};

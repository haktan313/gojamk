

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SpitForPickle.generated.h"

UCLASS()
class GOJAMK_API ASpitForPickle : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spit")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spit")
	TObjectPtr<USphereComponent> Sphere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spit")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spit")
	float BounceForce = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spit")
	float Damage = 10;
	UPROPERTY(BlueprintReadOnly,meta = (ExposeOnSpawn = true))
	TObjectPtr<AActor> target;
	
	ASpitForPickle();
	
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	virtual void BeginPlay() override;

	FTimerHandle spitTimer;
	void Spit();

	FTimerHandle destroyTimer;
	void DestroySelf();

	virtual void Tick(float DeltaTime) override;

};

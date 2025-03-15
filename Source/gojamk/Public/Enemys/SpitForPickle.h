

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
	UPROPERTY(BlueprintReadOnly,meta = (ExposeOnSpawn = true))
	TObjectPtr<AActor> target;
	

	ASpitForPickle();

	virtual void BeginPlay() override;

	FTimerHandle spitTimer;
	void Spit();

	virtual void Tick(float DeltaTime) override;

};

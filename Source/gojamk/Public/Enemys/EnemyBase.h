
#pragma once

#include "CoreMinimal.h"
#include "HAIBaseComponent.h"
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
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	
	AEnemyBase();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};

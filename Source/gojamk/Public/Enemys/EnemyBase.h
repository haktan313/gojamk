
#pragma once

#include "CoreMinimal.h"
#include "HAIBaseComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class GOJAMK_API AEnemyBase : public APawn
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	TObjectPtr<UHAIBaseComponent> HAIBaseComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AActor> targetActor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent* SkeletalMeshComponent;
	
	AEnemyBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};

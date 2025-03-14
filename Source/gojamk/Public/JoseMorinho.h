

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoseMorinho.generated.h"

UCLASS()
class GOJAMK_API AJoseMorinho : public ACharacter
{
	GENERATED_BODY()

	AJoseMorinho();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
};

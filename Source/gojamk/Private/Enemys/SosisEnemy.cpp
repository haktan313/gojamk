


#include "Enemys/SosisEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ASosisEnemy::ASosisEnemy()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASosisEnemy::BeginPlay()
{
	Super::BeginPlay();

	HAIBaseComponent->OnDoAction.AddDynamic(this, &ASosisEnemy::DoAction);
}

void ASosisEnemy::DoAction(int ActionID)
{
	switch (ActionID)
	{
		case 0:
			ThrowSosis();
			break;
	}
}

void ASosisEnemy::ThrowSosis()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController){return;}
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent){return;}
	TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("targetActor"));
	if (!TargetActor){return;}
	FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	ProjectileMovement->Velocity = Direction * 1000;
}

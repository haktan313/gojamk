


#include "gojamk/Public/Enemys/SosisEnemy.h"

ASosisEnemy::ASosisEnemy(): AEnemyBase()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

void ASosisEnemy::BeginPlay()
{
	OnActorHit.AddDynamic(this, &ASosisEnemy::OnHit);
	HAIBaseComponent->OnDoAction.AddDynamic(this, &ASosisEnemy::OnDoAction);
}

void ASosisEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Wall"))
	{
		
	}
}

void ASosisEnemy::OnDoAction(int ActionID)
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
	if(!targetActor){return;}
	FVector Direction = targetActor->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	ProjectileMovementComponent->Velocity = Direction * 1000;
}

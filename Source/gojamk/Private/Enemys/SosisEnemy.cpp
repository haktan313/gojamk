


#include "Enemys/SosisEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ASosisEnemy::ASosisEnemy()
{
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
}

void ASosisEnemy::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == TargetActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sosis hit the target"));
	}
}

void ASosisEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != TargetActor)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(bouncedEndTimer))
		{
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(bouncedEndTimer, this, &ASosisEnemy::BouncedEnd, 0.5f, false);
	}
}

void ASosisEnemy::BouncedEnd()
{
	HAIBaseComponent->OnActionEnd.Broadcast(E_DoActionResult::success);
	ProjectileMovement->Velocity = FVector::ZeroVector;
}

void ASosisEnemy::BeginPlay()
{
	Super::BeginPlay();

	HAIBaseComponent->OnDoAction.AddDynamic(this, &ASosisEnemy::DoAction);
	OnActorBeginOverlap.AddDynamic(this, &ASosisEnemy::OnOverlap);
	OnActorHit.AddDynamic(this, &ASosisEnemy::OnHit);
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
	Direction.Z = 0;
	ProjectileMovement->Velocity = Direction * BounceForce;
}

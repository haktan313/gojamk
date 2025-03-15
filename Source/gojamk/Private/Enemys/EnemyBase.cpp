


#include "Enemys/EnemyBase.h"

#include "AIController.h"
#include "HAIBaseComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
	HAIBaseComponent = CreateDefaultSubobject<UHAIBaseComponent>(TEXT("HAIBaseComponent"));
	HTokenSystemComponent = CreateDefaultSubobject<UHTokenSystemComponent>(TEXT("HTokenSystemComponent"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HAIBaseComponent->OnDoAction.AddDynamic(this, &AEnemyBase::DoAction);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlap);
	OnActorHit.AddDynamic(this, &AEnemyBase::OnHit);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor == TargetActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sosis hit the target"));
	}
}

void AEnemyBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != TargetActor)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(bouncedEndTimer))
		{
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(bouncedEndTimer, this, &AEnemyBase::BouncedEnd, 0.5f, false);
	}
}

void AEnemyBase::BouncedEnd()
{
	HAIBaseComponent->OnActionEnd.Broadcast(E_DoActionResult::success);
	ProjectileMovement->Velocity = FVector::ZeroVector;
}

void AEnemyBase::DoAction(int ActionID)
{
	switch (ActionID)
	{
	case 0:
		ThrowSosis();
		break;
	}
}

void AEnemyBase::ThrowSosis()
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


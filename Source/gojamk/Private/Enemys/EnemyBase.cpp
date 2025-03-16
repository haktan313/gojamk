


#include "Enemys/EnemyBase.h"

#include "AIController.h"
#include "HAIBaseComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	HAIBaseComponent = CreateDefaultSubobject<UHAIBaseComponent>(TEXT("HAIBaseComponent"));
	HTokenSystemComponent = CreateDefaultSubobject<UHTokenSystemComponent>(TEXT("HTokenSystemComponent"));
	HStatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("HStatHandler"));
	HStatHandler->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	HStatHandler->OnDamageResponse.AddDynamic(this, &AEnemyBase::OnDamageResponse);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

AActor* AEnemyBase::GetTargetActor()
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController){return nullptr;}
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent){return nullptr;}
	TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("targetActor"));
	return TargetActor;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HAIBaseComponent->OnDoAction.AddDynamic(this, &AEnemyBase::DoAction);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlap);
	OnActorHit.AddDynamic(this, &AEnemyBase::OnHit);
	if (Tags.Contains("Pickle"))
	{
		GetWorld()->GetTimerManager().SetTimer(spitTimer, this, &AEnemyBase::Spit, perSecondForSpit, true);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::OnDeath(UAnimMontage* DeathAnimation)
{
	if (Tags.Contains("Pickle"))
	{
		SplitPickle();
	}else
	{
		Destroy();
	}
}

void AEnemyBase::OnDamageResponse(UAnimMontage* DamageAnimation)
{
	
}

void AEnemyBase::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Tags.Contains("Sosis"))
	{
		if (OtherActor == GetTargetActor())
		{
			FS_DamageInfo damageInfo;
			damageInfo.AmountOfDamage = throwselfDamage;
			damageInfo.DamageReactionAnimation = nullptr;
			damageInfo.DeathReactionAnimation = nullptr;
			HStatHandler->DamageTo(damageInfo, OtherActor);
		}
	}
}

void AEnemyBase::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetTargetActor())
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
	if (GetTargetActor() == nullptr){return;}
	FVector Direction = GetTargetActor()->GetActorLocation() - GetActorLocation();
	Direction.Normalize();
	Direction.Z = 0;
	ProjectileMovement->Velocity = Direction * BounceForce;
}

void AEnemyBase::Spit()
{
	if (GetTargetActor())
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		ASpitForPickle* spit = GetWorld()->SpawnActor<ASpitForPickle>(SpitForPickleClass, GetActorLocation() + GetActorForwardVector() * 50, FRotator::ZeroRotator, SpawnParameters);
		if (spit)
		{
			spit->target = GetTargetActor();
		}
	}
}

void AEnemyBase::SplitPickle()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, GetActorLocation() + FVector(100, 0, 0), FRotator::ZeroRotator, SpawnParameters);
	GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, GetActorLocation() + FVector(-100, 0, 0), FRotator::ZeroRotator, SpawnParameters);
	GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, GetActorLocation() + FVector(0, -100, 0), FRotator::ZeroRotator, SpawnParameters);
	Destroy();
}


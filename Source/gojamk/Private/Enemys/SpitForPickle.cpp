
#include "Enemys/SpitForPickle.h"

#include "HStatHandler.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASpitForPickle::ASpitForPickle()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASpitForPickle::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->Tags.Contains("Player"))
	{
		UHStatHandler* statHandler = OtherActor->FindComponentByClass<UHStatHandler>();
		if (statHandler)
		{
			FS_DamageInfo damageInfo;
			damageInfo.AmountOfDamage = Damage;
			damageInfo.DamageReactionAnimation = nullptr;
			damageInfo.DeathReactionAnimation = nullptr;
			statHandler->DamageTo(damageInfo, OtherActor);
		}
		Destroy();
	}
}

void ASpitForPickle::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(spitTimer, this, &ASpitForPickle::Spit, 0.1f, false);
	OnActorBeginOverlap.AddDynamic(this, &ASpitForPickle::OnOverlapBegin);
}

void ASpitForPickle::Spit()
{
	if (target)
	{
		FVector targetLocation = target->GetVelocity() * FVector(.35f, .35f, .35f) + target->GetActorLocation();
		FVector direction = targetLocation - GetActorLocation();
		direction.Normalize();
		ProjectileMovement->Velocity = direction * BounceForce;
		GetWorld()->GetTimerManager().SetTimer(destroyTimer, this, &ASpitForPickle::DestroySelf, 2.f, false);
	}
}

void ASpitForPickle::DestroySelf()
{
	Destroy();
}

void ASpitForPickle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



#include "Enemys/SpitForPickle.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASpitForPickle::ASpitForPickle()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASpitForPickle::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Tags.Contains("Player"))
	{
		Destroy();
	}
}

void ASpitForPickle::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(spitTimer, this, &ASpitForPickle::Spit, 0.1f, false);
	OnActorHit.AddDynamic(this, &ASpitForPickle::OnHit);
}

void ASpitForPickle::Spit()
{
	if (target)
	{
		FVector targetLocation = target->GetVelocity() * FVector(.35f, .35f, .35f) + target->GetActorLocation();
		FVector direction = targetLocation - GetActorLocation();
		direction.Normalize();
		ProjectileMovement->Velocity = direction * BounceForce;
	}
}

void ASpitForPickle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


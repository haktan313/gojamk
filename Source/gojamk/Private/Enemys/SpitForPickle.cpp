
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

void ASpitForPickle::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(spitTimer, this, &ASpitForPickle::Spit, 0.1f, false);
}

void ASpitForPickle::Spit()
{
	if (target)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spit"));
		FVector direction = target->GetActorLocation() - GetActorLocation();
		direction.Normalize();
		ProjectileMovement->Velocity = direction * BounceForce;
	}
}

void ASpitForPickle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


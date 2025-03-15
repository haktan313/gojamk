


#include "Enemys/EnemyBase.h"
#include "HAIBaseComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Capsule);
	HAIBaseComponent = CreateDefaultSubobject<UHAIBaseComponent>(TEXT("HAIBaseComponent"));
	HTokenSystemComponent = CreateDefaultSubobject<UHTokenSystemComponent>(TEXT("HTokenSystemComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


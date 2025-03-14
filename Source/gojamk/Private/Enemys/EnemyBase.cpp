
#include "gojamk/Public/Enemys/EnemyBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	HAIBaseComponent = CreateDefaultSubobject<UHAIBaseComponent>(TEXT("HAIBaseComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController){return;}
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent){return;}
	BlackboardComponent->SetValueAsObject("targetActor", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	targetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



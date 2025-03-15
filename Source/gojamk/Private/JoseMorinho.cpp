
#include "gojamk/Public/JoseMorinho.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AJoseMorinho::AJoseMorinho()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	HTokenSystemComponent = CreateDefaultSubobject<UHTokenSystemComponent>(TEXT("HTokenSystemComponent"));
}

void AJoseMorinho::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJoseMorinho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



#include "gojamk/Public/JoseMorinho.h"

#include "HWidget_BaseStat.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void AJoseMorinho::OnDeath(UAnimMontage* DeathAnimation)
{
	FString currentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*currentLevel));
}

AJoseMorinho::AJoseMorinho()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	
	HTokenSystemComponent = CreateDefaultSubobject<UHTokenSystemComponent>(TEXT("HTokenSystemComponent"));
	HStatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("HStatHandler"));
	HStatHandler->OnDeath.AddDynamic(this, &AJoseMorinho::OnDeath);
	HStatHandler->statNameCurrentValue.Add(FString("tomato"),0);
	HStatHandler->statNameMaxValue.Add(FString("tomato"),3);
	HStatHandler->statNameCurrentValue.Add(FString("pickle"),0);
	HStatHandler->statNameMaxValue.Add(FString("pickle"),6);
}

void AJoseMorinho::BeginPlay()
{
	Super::BeginPlay();

	if (BaseStatWidgetClass)
	{
		UHWidget_BaseStat* BaseStatWidget = CreateWidget<UHWidget_BaseStat>(GetWorld(), BaseStatWidgetClass);
		if (BaseStatWidget)
		{
			BaseStatWidget->StatHandlerObjects.Add("Player", HStatHandler);
			BaseStatWidget->AddToViewport();
		}
	}
}

void AJoseMorinho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


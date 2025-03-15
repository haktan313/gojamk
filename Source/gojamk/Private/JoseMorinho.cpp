
#include "gojamk/Public/JoseMorinho.h"

#include "HWidget_BaseStat.h"
#include "Blueprint/UserWidget.h"
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
	HStatHandler = CreateDefaultSubobject<UHStatHandler>(TEXT("HStatHandler"));
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


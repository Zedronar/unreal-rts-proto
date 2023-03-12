#include "PlayerStartCamp.h"

APlayerStartCamp::APlayerStartCamp()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	UnitStartA = CreateDefaultSubobject<UBoxComponent>(TEXT("UnitStartA"));
	UnitStartA->SetRelativeLocation(FVector(160.0f, -150.0f, 0.0f));
	UnitStartA->SetupAttachment(Root);

	UnitStartB = CreateDefaultSubobject<UBoxComponent>(TEXT("UnitStartB"));
	UnitStartB->SetRelativeLocation(FVector(160.0f, 0, 0.0f));
	UnitStartB->SetupAttachment(Root);

	UnitStartC = CreateDefaultSubobject<UBoxComponent>(TEXT("UnitStartC"));
	UnitStartC->SetRelativeLocation(FVector(150.0f, 140.0f, 0.0f));
	UnitStartC->SetupAttachment(Root);

	StartingUnits = { UnitStartA, UnitStartB, UnitStartC };

	CameraLocationStart = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraLocationStart"));
	CameraLocationStart->SetRelativeLocation(FVector(90.0f, 0.0f, 560.0f));
	CameraLocationStart->SetupAttachment(Root);
	
	BuildingLocationStart = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingLocationStart"));
	BuildingLocationStart->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	BuildingLocationStart->SetupAttachment(Root);
}

void APlayerStartCamp::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerStartCamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#include "ParentBuilding.h"

AParentBuilding::AParentBuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AParentBuilding::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ParentBuilding"));
	}
}

void AParentBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
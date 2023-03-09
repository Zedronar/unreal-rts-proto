#include "PlayerStartCamp.h"

APlayerStartCamp::APlayerStartCamp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerStartCamp::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerStartCamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
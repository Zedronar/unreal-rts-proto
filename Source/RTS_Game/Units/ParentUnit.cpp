#include "ParentUnit.h"

AParentUnit::AParentUnit()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AParentUnit::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ParentUnit"));
	}
}

void AParentUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParentUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
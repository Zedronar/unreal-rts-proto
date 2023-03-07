// Fill out your copyright notice in the Description page of Project Settings.

#include "ParentBuilding.h"

// Sets default values
AParentBuilding::AParentBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AParentBuilding::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ParentBuilding"));
	}
}

// Called every frame
void AParentBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
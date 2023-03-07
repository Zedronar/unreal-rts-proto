// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStartCamp.h"

// Sets default values
APlayerStartCamp::APlayerStartCamp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerStartCamp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerStartCamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
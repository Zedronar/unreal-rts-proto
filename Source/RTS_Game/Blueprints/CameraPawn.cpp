// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CameraPawn"));
	}
}

void ACameraPawn::MouseX()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	float LocationX;
	float LocationY;
	if (!PlayerController->GetMousePosition(LocationX, LocationY))
	{
		return;
	};

	int32 SizeX;
	int32 SizeY;
	PlayerController->GetViewportSize(SizeX, SizeY);

	if (LocationX / SizeX > 0.98)
	{
		UpdateDeltaLocationY(1);
	} else if (LocationX / SizeX < 0.02)
	{
		UpdateDeltaLocationY(-1);
	}
}

void ACameraPawn::MouseY()
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	float LocationX;
	float LocationY;
	if (!PlayerController->GetMousePosition(LocationX, LocationY))
	{
		return;
	};

	int32 SizeX;
	int32 SizeY;
	PlayerController->GetViewportSize(SizeX, SizeY);

	if (LocationY / SizeY < 0.02)
	{
		UpdateDeltaLocationX(1);
	} else if (LocationY / SizeY > 0.98)
	{
		UpdateDeltaLocationX(-1);
	}
}

void ACameraPawn::MouseWheelUp()
{
	FVector DeltaLocation = FVector::UnitZ();
	DeltaLocation.Z = this->ZoomSpeed * -1;
	this->AddActorLocalOffset(DeltaLocation);

}

void ACameraPawn::MouseWheelDown()
{
	FVector DeltaLocation = FVector::UnitZ();
	DeltaLocation.Z = this->ZoomSpeed;
	this->AddActorLocalOffset(DeltaLocation);
}

void ACameraPawn::UpdateDeltaLocationY(const int32 Direction)
{
	FVector DeltaLocation = FVector::UnitY();
	DeltaLocation.Y = UGameplayStatics::GetWorldDeltaSeconds(this) * this->ScrollSpeed * Direction;
	this->AddActorLocalOffset(DeltaLocation);
}

void ACameraPawn::UpdateDeltaLocationX(const int32 Direction)
{
	FVector DeltaLocation = FVector::UnitX();
	DeltaLocation.X = UGameplayStatics::GetWorldDeltaSeconds(this) * this->ScrollSpeed * Direction;
	this->AddActorLocalOffset(DeltaLocation);
}

// Called every frame
void ACameraPawn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
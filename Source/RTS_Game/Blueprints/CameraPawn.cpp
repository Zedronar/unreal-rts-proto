#include "CameraPawn.h"
#include "Kismet/GameplayStatics.h"

ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void ACameraPawn::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// TODO: Use UE5 Enhanced Input plugin
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACameraPawn::MoveY);
	PlayerInputComponent->BindAxis(TEXT("Backward"), this, &ACameraPawn::MoveY);
	PlayerInputComponent->BindAxis(TEXT("Left"), this, &ACameraPawn::MoveX);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACameraPawn::MoveX);

	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ACameraPawn::MouseX);
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ACameraPawn::MouseY);
	PlayerInputComponent->BindAxis(TEXT("Wheel"), this, &ACameraPawn::Wheel);
}

void ACameraPawn::MouseX(float AxisValue)
{
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

void ACameraPawn::MouseY(float AxisValue)
{
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

void ACameraPawn::Wheel(const float AxisValue)
{
	FVector DeltaLocation = FVector::UnitZ();
	DeltaLocation.Z = this->ZoomSpeed * AxisValue * -1; // Invert mouse wheel
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

void ACameraPawn::MoveY(const float AxisValue)
{
	UpdateDeltaLocationX(AxisValue);
}

void ACameraPawn::MoveX(const float AxisValue)
{
	UpdateDeltaLocationY(AxisValue);
}
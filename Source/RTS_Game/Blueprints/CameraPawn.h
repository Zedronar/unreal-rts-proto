#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CameraPawn.generated.h"

UCLASS()
class RTS_GAME_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MouseX(float AxisValue);

	void MouseY(float AxisValue);

	void Wheel(float AxisValue);

	void MoveY(float AxisValue);

	void MoveX(float AxisValue);

	void UpdateDeltaLocationY(int32 Direction);

	void UpdateDeltaLocationX(int32 Direction);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ScrollSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ZoomSpeed = 25;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

private:
	UPROPERTY()
	const APlayerController* PlayerController;
};
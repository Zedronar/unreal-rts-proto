// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class RTS_GAME_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MouseX();

	UFUNCTION(BlueprintCallable)
	void MouseY();

	UFUNCTION(BlueprintCallable)
	void MouseWheelUp();

	UFUNCTION(BlueprintCallable)
	void MouseWheelDown();
	
private:
	void UpdateDeltaLocationY(int32 Direction);

	void UpdateDeltaLocationX(int32 Direction);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ScrollSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ZoomSpeed = 25;
};

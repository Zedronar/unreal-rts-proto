// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Units/ParentUnit.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentBuilding.generated.h"

UCLASS()
class RTS_GAME_API AParentBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductionTimerGranularity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductionTimeNeeded = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductionTimeSpent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductionProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelUpTimeSpent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelUpProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBuildingLevel = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLevelingUp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsProducingUnit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AParentUnit>> UnitProductionQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AParentUnit> UnitBeingProduced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	UTexture2D* Image2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	float BuildTime = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 LevelUpCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	float LevelUpTimeNeeded = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	TArray<TSubclassOf<AParentUnit>> BuildableUnits;
};

#pragma once

#include "../Units/ParentUnit.h"
#include "BuildingData.h"

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "EBuildingNames.h"
#include "GameFramework/Actor.h"
#include "ParentBuilding.generated.h"

UCLASS()
class RTS_GAME_API AParentBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	AParentBuilding();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool IsUnitProductionComplete();

	UFUNCTION(BlueprintCallable)
	void SpawnUnit(UBoxComponent* UnitSpawnPoint);

	UFUNCTION(BlueprintCallable)
	void StartProducingNextUnit();

	UFUNCTION(BlueprintCallable)
	void StartLevelUp(int32 PlayerResourceAmount);

	UFUNCTION(BlueprintCallable)
	void LevelUpTick();

	UFUNCTION(BlueprintCallable)
	void SetupTeamColor(UStaticMeshComponent* StaticMeshComponent);

private:
	bool GetBuildingRowData(const FBuilding*& BuildingRowData) const;

	bool GetUnitRowData(const FUnit*& UnitRowData) const;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	EBuildingNames BuildingName = EBuildingNames::CommandCenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	FLinearColor TeamColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildingData;

	// TODO: Refactor and call unit to get this
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* UnitData;
};

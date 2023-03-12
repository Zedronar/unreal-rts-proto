#pragma once

#include "../DataTableSubsystem.h"
#include "../Units/ParentUnit.h"
#include "../Buildings/ParentBuilding.h"
#include "PlayerStartCamp.h"
#include "I_RTS.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PlayerController.generated.h"

/**
 *
 */
UCLASS()
class RTS_GAME_API ARTS_PlayerController : public APlayerController, public II_RTS
{
	GENERATED_BODY()

public:
	ARTS_PlayerController();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReduceResourceAmount(const int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncrementResourceAmount(const int32 Amount);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ServerAddUnitToQueue(AParentBuilding* Building, TSubclassOf<AParentUnit> Unit);

	UFUNCTION(Server, Reliable)
	void ServerAddUnitToQueueNetwork(AParentBuilding* Building, TSubclassOf<AParentUnit> Unit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartBuildingConstruction(TSubclassOf<AParentBuilding> Building);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupPlayerStart2(APlayerStartCamp* PlayerStartCamp, int32 PlayerTeamNumber, FLinearColor PlayerTeamColor);

protected:
	UFUNCTION(BlueprintCallable)
	void ConstructBuildingTick(UBoxComponent* StartingBuildingSpawnPoint);

private:
	bool DeductResourceCost(const int32 Cost);

	float GetRandomFloatWithGap() const;

	FTransform GetNewBuildingTransform(const UBoxComponent* StartingBuildingSpawnPoint) const;

	void SpawnBuilding(const FTransform Transform, const TSubclassOf<AParentBuilding> Subclass);

	void SpawnUnit(const FTransform Transform, const TSubclassOf<AParentUnit> Subclass, int32 StartingUnitLevel);

protected:
	#pragma region BuildingConstruction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	bool IsConstructingBuilding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	float ConstructionProgress = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	float ConstructionTimeSpent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	float ConstructionTimeNeeded = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	float ConstructionTimerGranularity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	TSubclassOf<AParentBuilding> BuildingBeingConstructed;
	#pragma endregion BuildingConstruction

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 ResourceAmount = 200; // For testing purposes

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TeamColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLeftMousePressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightClickLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AParentBuilding* SelectedBuilding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AParentBuilding> InitialBuildingClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AParentUnit> InitialUnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	APlayerStartCamp* StartCamp;

private:
	UPROPERTY()
	UDataTableSubsystem* DataTableSubsystem = nullptr;
};

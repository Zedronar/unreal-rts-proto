#pragma once

#include "../DataTableSubsystem.h"
#include "../Units/ParentUnit.h"
#include "../Buildings/BuildingData.h"
#include "../Buildings/ParentBuilding.h"
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

protected:
	UFUNCTION(BlueprintCallable)
	void ConstructBuildingTick(UBoxComponent* StartingBuildingSpawnPoint);

private:
	bool DeductResourceCost(const int32 Cost);

	float GetRandomFloatWithGap() const;

	void GetNewBuildingTransform(const UBoxComponent* StartingBuildingSpawnPoint, const FTransform*& NewTransform) const;

	void SpawnBuilding(const FTransform* NewTransform);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildingData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	UDataTable* UnitData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int32 ResourceAmount = 0;

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

private:
	UPROPERTY()
	UDataTableSubsystem* DataTableSubsystem = nullptr;
};

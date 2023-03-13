#pragma once

#include "../Units/ParentUnit.h"
#include "../Buildings/ParentBuilding.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_RTS.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UI_RTS : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_GAME_API II_RTS
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReduceResourceAmount(const int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncrementResourceAmount(const int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClientShowNotEnoughResources();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartBuildingConstruction(TSubclassOf<AParentBuilding> Building);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ServerAddUnitToQueue(AParentBuilding* Building, TSubclassOf<AParentUnit> Unit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetupPlayerStart2(APlayerStartCamp* PlayerStartCamp, int32 PlayerTeamNumber, FLinearColor PlayerTeamColor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MarqueePressed();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MarqueeHeld();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MarqueeReleased();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SelectThis();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeselectThis();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetIsConstructingBuilding();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetConstructionProgress();
};

#pragma once

#include "../Buildings/ParentBuilding.h"
#include "../Buildings/BuildingData.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PlayerController.generated.h"

/**
 *
 */
UCLASS()
class RTS_GAME_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor TeamColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLeftMousePressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RightClickLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResourceAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AParentBuilding* SelectedBuilding;
};

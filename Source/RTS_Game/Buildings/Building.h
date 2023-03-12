#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Building.generated.h"

// Forward declaration
class AParentUnit;

/**
 *
 */
USTRUCT(BlueprintType)
struct RTS_GAME_API FBuilding : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitialLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LevelUpCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelUpTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AParentUnit>> BuildableUnits;
};

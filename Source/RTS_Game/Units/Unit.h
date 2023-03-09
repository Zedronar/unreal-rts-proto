#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Unit.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct RTS_GAME_API FUnit : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};

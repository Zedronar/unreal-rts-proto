#pragma once

#include "CoreMinimal.h"
#include "EUnitNames.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EUnitNames : uint8
{
	ResourceTruck = 0 UMETA(DisplayName = "ResourceTruck"),
	UnitStyle1 = 1 UMETA(DisplayName = "UnitStyle1"),
	UnitStyle2 = 2 UMETA(DisplayName = "UnitStyle2"),
	Plane = 3 UMETA(DisplayName = "Plane"),
	Car = 4 UMETA(DisplayName = "Car"),
	Motorcycle = 5 UMETA(DisplayName = "Motorcycle"),
    Max UMETA(Hidden),
};
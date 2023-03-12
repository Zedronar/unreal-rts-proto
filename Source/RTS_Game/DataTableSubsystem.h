#pragma once

#include "Units/Unit.h"
#include "Units/EUnitNames.h"
#include "Buildings/Building.h"
#include "Buildings/EBuildingNames.h"

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataTableSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API UDataTableSubsystem final : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UDataTableSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FBuilding* GetBuildingRowData(EBuildingNames BuildingName) const;

	FUnit* GetUnitRowData(EUnitNames UnitName) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* BuildingData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* UnitData;
};

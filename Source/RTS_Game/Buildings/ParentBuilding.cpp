#include "ParentBuilding.h"

AParentBuilding::AParentBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetWorld())
	{
		// DataTable - Load
		static ConstructorHelpers::FObjectFinder<UDataTable> BuildingDataObject(TEXT("DataTable'/Game/Buildings/BuildingsDataTable.BuildingsDataTable'"));
		if (BuildingDataObject.Succeeded())
		{
			BuildingData = BuildingDataObject.Object;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BUILDINGS DATATABLE NOT FOUND"));
		}

		// TODO
		// DataTable - Load
		static ConstructorHelpers::FObjectFinder<UDataTable> UnitDataObject(TEXT("DataTable'/Game/Units/UnitsDataTable.UnitsDataTable'"));
		if (UnitDataObject.Succeeded())
		{
			UnitData = UnitDataObject.Object;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UNITS DATATABLE NOT FOUND"));
		}
	}
}

void AParentBuilding::BeginPlay()
{
	Super::BeginPlay();

	// TODO - Refactor to function
	TEnumAsByte EnumVar = this->BuildingName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrBuildingName =  MyEnumValueText.ToString();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ParentBuilding - " + StrBuildingName));
	}

	// DataTable - Consume data
	static const FString ContextString(StrBuildingName);
	if (const FBuilding* BuildingRowData = BuildingData->FindRow<FBuilding>(FName(StrBuildingName), ContextString, true))
	{
		this->Cost = BuildingRowData->Cost;
		this->BuildTime = BuildingRowData->BuildTime;
		this->Health = BuildingRowData->Health;
		this->Level = BuildingRowData->InitialLevel;
		this->LevelUpCost = BuildingRowData->LevelUpCost;
		this->LevelUpTimeNeeded = BuildingRowData->LevelUpTime;
		this->BuildableUnits = BuildingRowData->BuildableUnits;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DATATABLE ROW NOT FOUND"));
	}
}

bool AParentBuilding::IsProductionDone()
{
	// Update progress
	this->ProductionTimeSpent += this->ProductionTimerGranularity;
	this->ProductionProgress = this->ProductionTimeSpent / this->ProductionTimeNeeded;

	if (this->ProductionProgress >= 1.0f)
	{
		// Production complete
		return true;
	}

	return false;
}

void AParentBuilding::StartProducingNextUnit()
{
	// Check if there are units in the queue
	if (this->UnitProductionQueue.Num() == 0)
	{
		// No units in queue
		return;
	}

	// Get the first unit in the queue
	this->UnitBeingProduced = this->UnitProductionQueue[0];

	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(UnitBeingProduced->GetDefaultObject(true));
	const TEnumAsByte EnumVar = DefaultSubclassObject->UnitName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrUnitName =  MyEnumValueText.ToString();

	// DataTable - Consume data
	static const FString ContextString(StrUnitName);
	if (const FUnit* UnitRowData = UnitData->FindRow<FUnit>(FName(StrUnitName), ContextString, true))
	{
		// Get default build time from unit being produced
		ProductionTimeNeeded = UnitRowData->BuildTime;

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DATATABLE ROW NOT FOUND"));
	}

	// Remove unit from queue
	this->UnitProductionQueue.RemoveAt(0);

	// Start production
	this->IsProducingUnit = true;
}

void AParentBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

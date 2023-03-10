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

bool AParentBuilding::IsUnitProductionComplete()
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

void AParentBuilding::SpawnUnit(UBoxComponent* UnitSpawnPoint)
{
	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(UnitBeingProduced->GetDefaultObject(true));
	const TEnumAsByte EnumVar = DefaultSubclassObject->UnitName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrUnitName =  MyEnumValueText.ToString();

	// DataTable - Consume data
	static const FString ContextString(StrUnitName);
	const FUnit* UnitRowData = UnitData->FindRow<FUnit>(FName(StrUnitName), ContextString, true);
	if (!UnitRowData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DATATABLE ROW NOT FOUND"));
		return;
	}

	// Spawn unit
	AParentUnit* NewUnit = GetWorld()->SpawnActorDeferred<AParentUnit>(UnitBeingProduced, UnitSpawnPoint->GetComponentTransform());
	NewUnit->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	NewUnit->TeamNumber = this->TeamNumber;
	NewUnit->TeamColor = this->TeamColor;
	NewUnit->Level = this->Level; // Building level is carried over to units
	NewUnit->Speed = UnitRowData->Speed;
	NewUnit->Cost = UnitRowData->Cost;
	NewUnit->BuildTime = UnitRowData->BuildTime;
	NewUnit->Health = UnitRowData->Health;
	NewUnit->Damage = UnitRowData->Damage;
	NewUnit->Description = UnitRowData->Description;
	NewUnit->FinishSpawning(UnitSpawnPoint->GetComponentTransform());

	// Reset production
	this->IsProducingUnit = false;
	this->ProductionProgress = 0.0f;
	this->ProductionTimeSpent = 0.0f;
	this->UnitBeingProduced = nullptr;
}

void AParentBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

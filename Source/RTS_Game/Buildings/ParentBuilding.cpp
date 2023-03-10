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

	const FBuilding* BuildingRowData;
	if (!GetBuildingRowData(BuildingRowData))
		return;

	this->Cost = BuildingRowData->Cost;
	this->BuildTime = BuildingRowData->BuildTime;
	this->Health = BuildingRowData->Health;
	this->Level = BuildingRowData->InitialLevel;
	this->LevelUpCost = BuildingRowData->LevelUpCost;
	this->LevelUpTimeNeeded = BuildingRowData->LevelUpTime;
	this->BuildableUnits = BuildingRowData->BuildableUnits;
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

	const FUnit* UnitRowData;
	if (!GetUnitRowData(UnitRowData))
		return;
	
	// Get default build time from unit being produced
	ProductionTimeNeeded = UnitRowData->BuildTime;

	// Remove unit from queue
	this->UnitProductionQueue.RemoveAt(0);

	// Start production
	this->IsProducingUnit = true;
}

void AParentBuilding::SpawnUnit(UBoxComponent* UnitSpawnPoint)
{
	const FUnit* UnitRowData;
	if (!GetUnitRowData(UnitRowData))
		return;

	// Spawn unit
	AParentUnit* NewUnit = GetWorld()->SpawnActorDeferred<AParentUnit>(
		UnitBeingProduced,
		UnitSpawnPoint->GetComponentTransform(),
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
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

void AParentBuilding::StartLevelUp(const int32 PlayerResourceAmount)
{
	if (this->Level >= this->MaxBuildingLevel)
	{
		// Building is already at max level
		return;
	}

	if (PlayerResourceAmount < this->LevelUpCost)
	{
		// Player does not have enough resources
		return;
	}

	// Start level up
	this->IsLevelingUp = true;
}

void AParentBuilding::LevelUpTick()
{
	if (!this->IsLevelingUp)
	{
		return;
	}

	// Update progress
	this->LevelUpTimeSpent += this->ProductionTimerGranularity;
	this->LevelUpProgress = this->LevelUpTimeSpent / this->LevelUpTimeNeeded;

	if (this->LevelUpProgress < 1.0f)
	{
		// Still leveling up
		return;
	}

	// Level up complete
	this->Level += 1;
	this->LevelUpProgress = 0;
	this->LevelUpTimeSpent= 0;
	this->IsLevelingUp = false;
}

void AParentBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParentBuilding::SetupTeamColor(UStaticMeshComponent* StaticMeshComponent)
{
	UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
	if (Material != nullptr)
	{
		UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		if (MaterialInstance != nullptr)
		{
			MaterialInstance->SetVectorParameterValue("TeamColor", TeamColor);
			StaticMeshComponent->SetMaterial(0, MaterialInstance);
		}
	}
}

bool AParentBuilding::GetBuildingRowData(const FBuilding*& BuildingRowData) const
{
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
	BuildingRowData = BuildingData->FindRow<FBuilding>(FName(StrBuildingName), ContextString, true);
	if (!BuildingRowData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BUILDINGS DATATABLE ROW NOT FOUND"));
		return false;
	}

	return true;
}

bool AParentBuilding::GetUnitRowData(const FUnit*& UnitRowData) const
{
	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(UnitBeingProduced->GetDefaultObject(true));

	const TEnumAsByte EnumVar = DefaultSubclassObject->UnitName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrUnitName =  MyEnumValueText.ToString();

	// DataTable - Consume data
	static const FString ContextString(StrUnitName);
	UnitRowData = UnitData->FindRow<FUnit>(FName(StrUnitName), ContextString, true);
	if (!UnitRowData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UNITS DATATABLE ROW NOT FOUND"));
		return false;
	}

	return true;
}
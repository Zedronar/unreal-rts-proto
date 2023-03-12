#include "ParentBuilding.h"

AParentBuilding::AParentBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetWorld() && GetGameInstance())
	{
		this->DataTableSubsystem = GetGameInstance()->GetSubsystem<UDataTableSubsystem>();
	}
}

void AParentBuilding::Initialize(TSubclassOf<AParentBuilding> Subclass, FTransform Transform, int32 ParentTeamNumber, FLinearColor ParentTeamColor)
{
	const AParentBuilding* DefaultSubclassObject = Cast<AParentBuilding>(Subclass->GetDefaultObject(true));
	const FBuilding* BuildingRowData = DataTableSubsystem->GetRowData(DefaultSubclassObject->BuildingName);

	this->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->TeamNumber = ParentTeamNumber;
	this->TeamColor = ParentTeamColor;
	this->Cost = BuildingRowData->Cost;
	this->BuildTime = BuildingRowData->BuildTime;
	this->Health = BuildingRowData->Health;
	this->Level = BuildingRowData->InitialLevel;
	this->LevelUpCost = BuildingRowData->LevelUpCost;
	this->LevelUpTimeNeeded = BuildingRowData->LevelUpTime;
	this->BuildableUnits = BuildingRowData->BuildableUnits;
	this->FinishSpawning(Transform);
}


void AParentBuilding::BeginPlay()
{
	Super::BeginPlay();
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

	// Get data from DataTable
	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(UnitBeingProduced->GetDefaultObject(true));
	const FUnit* UnitRowData = this->DataTableSubsystem->GetRowData(DefaultSubclassObject->UnitName);
	
	// Get default build time from unit being produced
	ProductionTimeNeeded = UnitRowData->BuildTime;

	// Remove unit from queue
	this->UnitProductionQueue.RemoveAt(0);

	// Start production
	this->IsProducingUnit = true;
}

void AParentBuilding::SpawnUnit(UBoxComponent* UnitSpawnPoint)
{
	// Spawn unit deferred
	AParentUnit* NewUnit = GetWorld()->SpawnActorDeferred<AParentUnit>(
		UnitBeingProduced,
		UnitSpawnPoint->GetComponentTransform(),
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);
	NewUnit->Initialize(
		UnitBeingProduced,
		UnitSpawnPoint->GetComponentTransform(),
		this->TeamNumber,
		this->TeamColor,
		this->Level // Building level is carried over to units
	);

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

void AParentBuilding::AddUnitToQueue(TSubclassOf<AParentUnit> Unit)
{
	this->UnitProductionQueue.Add(Unit);
}
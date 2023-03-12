#include "RTS_PlayerController.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetWorld() && GetGameInstance())
	{
		this->DataTableSubsystem = GetGameInstance()->GetSubsystem<UDataTableSubsystem>();
	}
}

bool ARTS_PlayerController::DeductResourceCost(const int32 Cost)
{
	if (this->ResourceAmount >= Cost)
	{
		this->ResourceAmount -= Cost;
		return true;
	}

	return false;
}

void ARTS_PlayerController::ServerAddUnitToQueue_Implementation(AParentBuilding* Building, TSubclassOf<AParentUnit> Unit)
{
	ServerAddUnitToQueueNetwork_Implementation(Building, Unit);
}

void ARTS_PlayerController::ServerAddUnitToQueueNetwork_Implementation(AParentBuilding* Building, TSubclassOf<AParentUnit> Unit)
{
	// Deduct cost
	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(Unit->GetDefaultObject(true));
	const FUnit* UnitRowData = this->DataTableSubsystem->GetUnitRowData(DefaultSubclassObject->UnitName);

	bool Deducted = DeductResourceCost(UnitRowData->Cost);
	if (!Deducted)
	{
		Execute_ClientShowNotEnoughResources(this);
		return;
	}

	// Add unit to queue
	Building->AddUnitToQueue(Unit);
}

void ARTS_PlayerController::ReduceResourceAmount_Implementation(const int32 Amount)
{
	bool Deducted = DeductResourceCost(Amount);
	if (!Deducted)
	{
		Execute_ClientShowNotEnoughResources(this);
		return;
	}
}

void ARTS_PlayerController::IncrementResourceAmount_Implementation(const int32 Amount)
{
	this->ResourceAmount += Amount;
}

void ARTS_PlayerController::StartBuildingConstruction_Implementation(TSubclassOf<AParentBuilding> Building)
{
	if (this->IsConstructingBuilding)
	{
		return;
	}

	// Deduct cost
	const AParentBuilding* DefaultSubclassObject = Cast<AParentBuilding>(Building->GetDefaultObject(true));
	const FBuilding* BuildingRowData = this->DataTableSubsystem->GetBuildingRowData(DefaultSubclassObject->BuildingName);

	bool Deducted = DeductResourceCost(BuildingRowData->Cost);
	if (!Deducted)
	{
		Execute_ClientShowNotEnoughResources(this);
		return;
	}

	this->IsConstructingBuilding = true;
	this->BuildingBeingConstructed = Building;
	this->ConstructionTimeNeeded = BuildingRowData->BuildTime;
}

void ARTS_PlayerController::GetNewBuildingTransform(const UBoxComponent* StartingBuildingSpawnPoint, const FTransform*& NewTransform) const
{
	const FTransform StartTransform = StartingBuildingSpawnPoint->GetComponentTransform();
	const FVector OldTransformLocation = StartTransform.GetLocation();
	const FVector* NewTransformLocation = new FVector(
		OldTransformLocation.X + GetRandomFloatWithGap(),
		OldTransformLocation.Y + GetRandomFloatWithGap(),
		OldTransformLocation.Z
	);
	NewTransform = new FTransform(
		StartingBuildingSpawnPoint->GetComponentRotation(),
		*NewTransformLocation
	);
}

void ARTS_PlayerController::SetupPlayerStart2_Implementation(APlayerStartCamp* PlayerStartCamp, int32 PlayerTeamNumber, FLinearColor PlayerTeamColor)
{
	if (!this->HasAuthority())
	{
		return;
	}

	this->TeamNumber = PlayerTeamNumber;
	this->TeamColor = PlayerTeamColor;

}

void ARTS_PlayerController::ConstructBuildingTick(UBoxComponent* StartingBuildingSpawnPoint)
{
	if (!this->IsConstructingBuilding)
	{
		return;
	}

	this->ConstructionTimeSpent += this->ConstructionTimerGranularity;

	this->ConstructionProgress = this->ConstructionTimeSpent / this->ConstructionTimeNeeded;

	if (this->ConstructionTimeSpent < this->ConstructionTimeNeeded)
	{
		return;
	}

	// Calculate random location to spawn new building (near starting camp)
	const FTransform* NewTransform;
	GetNewBuildingTransform(StartingBuildingSpawnPoint, NewTransform);

	// Spawn
	SpawnBuilding(NewTransform);

	// Reset production
	this->IsConstructingBuilding = false;
	this->BuildingBeingConstructed = nullptr;
	this->ConstructionTimeSpent = 0.0f;
	this->ConstructionProgress = 0.0f;
}

float ARTS_PlayerController::GetRandomFloatWithGap() const
{
	const float Random1 = FMath::RandRange(-400.0f, -100.0f);
	const float Random2 = FMath::RandRange(100.0f, 400.0f);
	const float Choices[2] = {Random1, Random2};
	const int Index = FMath::RandRange(0, 1);
	const float RandomFloat = Choices[Index];
	return RandomFloat;
}

void ARTS_PlayerController::SpawnBuilding(const FTransform* NewTransform)
{
	const AParentBuilding* DefaultSubclassObject = Cast<AParentBuilding>(BuildingBeingConstructed->GetDefaultObject(true));
	const FBuilding* BuildingRowData = this->DataTableSubsystem->GetBuildingRowData(DefaultSubclassObject->BuildingName);
	AParentBuilding* NewBuilding = GetWorld()->SpawnActorDeferred<AParentBuilding>(
		this->BuildingBeingConstructed,
		*NewTransform,
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	NewBuilding->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	NewBuilding->TeamNumber = this->TeamNumber;
	NewBuilding->TeamColor = this->TeamColor;
	NewBuilding->Cost = BuildingRowData->Cost;
	NewBuilding->BuildTime = BuildingRowData->BuildTime;
	NewBuilding->Health = BuildingRowData->Health;
	NewBuilding->Level = BuildingRowData->InitialLevel;
	NewBuilding->LevelUpCost = BuildingRowData->LevelUpCost;
	NewBuilding->LevelUpTimeNeeded = BuildingRowData->LevelUpTime;
	NewBuilding->BuildableUnits = BuildingRowData->BuildableUnits;
	NewBuilding->FinishSpawning(*NewTransform);
}
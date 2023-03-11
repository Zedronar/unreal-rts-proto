#include "RTS_PlayerController.h"

ARTS_PlayerController::ARTS_PlayerController()
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
	}
}

void ARTS_PlayerController::IncrementResourceAmount_Implementation(const int32 Amount)
{
	this->ResourceAmount += Amount;
}

//void ARTS_PlayerController::ProduceUnit_Implementation()
//{
//	// TODO
//}

void ARTS_PlayerController::ConstructBuilding_Implementation(TSubclassOf<AParentBuilding> Building)
{
	this->IsConstructingBuilding = true;

	this->BuildingBeingConstructed = Building;

	const AParentBuilding* DefaultSubclassObject = Cast<AParentBuilding>(Building->GetDefaultObject(true));
	const FBuilding* BuildingRowData = GetBuildingRowData(DefaultSubclassObject->BuildingName);

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

FBuilding* ARTS_PlayerController::GetBuildingRowData(EBuildingNames BuildingName) const
{
	const TEnumAsByte EnumVar = BuildingName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrBuildingName =  MyEnumValueText.ToString();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ParentBuilding - " + StrBuildingName));
	}

	// DataTable - Read data
	static const FString ContextString(StrBuildingName);
	return BuildingData->FindRow<FBuilding>(FName(StrBuildingName), ContextString, true);
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
	const FBuilding* BuildingRowData = GetBuildingRowData(DefaultSubclassObject->BuildingName);
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
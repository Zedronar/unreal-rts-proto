
#include "DataTableSubsystem.h"

UDataTableSubsystem::UDataTableSubsystem()
{
	if (UObject::GetWorld())
	{
		// DataTable - Load
		const ConstructorHelpers::FObjectFinder<UDataTable> BuildingDataObject(TEXT("DataTable'/Game/Buildings/BuildingsDataTable.BuildingsDataTable'"));
		if (BuildingDataObject.Succeeded())
		{
			BuildingData = BuildingDataObject.Object;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BUILDINGS DATATABLE NOT FOUND"));
		}

		const ConstructorHelpers::FObjectFinder<UDataTable> UnitDataObject(TEXT("DataTable'/Game/Units/UnitsDataTable.UnitsDataTable'"));
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

void UDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("DATATABLE SUBSYSTEM INIT"));

	Super::Initialize(Collection);
}

void UDataTableSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

FBuilding* UDataTableSubsystem::GetBuildingRowData(EBuildingNames BuildingName) const
{
	const TEnumAsByte EnumVar = BuildingName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrBuildingName =  MyEnumValueText.ToString();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ParentBuilding - " + StrBuildingName));
	}

	// Read data from Buildings DataTable
	static const FString ContextString(StrBuildingName);
	return BuildingData->FindRow<FBuilding>(FName(StrBuildingName), ContextString, true);
}

FUnit* UDataTableSubsystem::GetUnitRowData(EUnitNames UnitName) const
{
	const TEnumAsByte EnumVar = UnitName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrUnitName =  MyEnumValueText.ToString();

	// Read data from Units DataTable
	static const FString ContextString(StrUnitName);
	return UnitData->FindRow<FUnit>(FName(StrUnitName), ContextString, true);
}

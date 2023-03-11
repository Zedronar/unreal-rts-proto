#include "ParentUnit.h"

AParentUnit::AParentUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetWorld())
	{
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

bool AParentUnit::GetUnitRowData(const FUnit*& UnitRowData) const
{
	TEnumAsByte EnumVar = this->UnitName;
	FText MyEnumValueText;
	UEnum::GetDisplayValueAsText(EnumVar, MyEnumValueText);
	FString StrUnitName =  MyEnumValueText.ToString();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ParentUnit - " + StrUnitName));
	}

	// DataTable - Read data
	static const FString ContextString(StrUnitName);
	UnitRowData = UnitData->FindRow<FUnit>(FName(StrUnitName), ContextString, true);
	if (!UnitRowData)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DATATABLE ROW NOT FOUND"));
		return true;
	}
	return false;
}

void AParentUnit::BeginPlay()
{
	Super::BeginPlay();

	const FUnit* UnitRowData;
	if (GetUnitRowData(UnitRowData)) return;

	this->Speed = UnitRowData->Speed;
	this->Cost = UnitRowData->Cost;
	this->BuildTime = UnitRowData->BuildTime;
	this->Health = UnitRowData->Health;
	this->Damage = UnitRowData->Damage;
	this->Description = UnitRowData->Description;
}

void AParentUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParentUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AParentUnit::SetupTeamColor()
{
	for (const auto MeshComponent : MeshesForTeamColoring)
	{
		if (MeshComponent != nullptr)
		{
			UMaterialInterface* Material = MeshComponent->GetMaterial(0);
			if (Material != nullptr)
			{
				UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
				if (MaterialInstance != nullptr)
				{
					MaterialInstance->SetVectorParameterValue("TeamColor", TeamColor);
					MeshComponent->SetMaterial(0, MaterialInstance);
				}
			}
		}
	}
}

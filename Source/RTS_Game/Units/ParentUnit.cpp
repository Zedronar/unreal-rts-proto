#include "ParentUnit.h"

AParentUnit::AParentUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetWorld() && GetGameInstance())
	{
		this->DataTableSubsystem = GetGameInstance()->GetSubsystem<UDataTableSubsystem>();
	}
}

void AParentUnit::Init(TSubclassOf<AParentUnit> Subclass, FTransform Transform, int32 ParentTeamNumber, FLinearColor ParentTeamColor, int32 StartingLevel)
{
	const AParentUnit* DefaultSubclassObject = Cast<AParentUnit>(Subclass->GetDefaultObject(true));
	const FUnit* UnitRowData = DataTableSubsystem->GetRowData(DefaultSubclassObject->UnitName);

	this->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->TeamNumber = ParentTeamNumber;
	this->TeamColor = ParentTeamColor;
	this->Level = StartingLevel;
	this->Speed = UnitRowData->Speed;
	this->Cost = UnitRowData->Cost;
	this->BuildTime = UnitRowData->BuildTime;
	this->Health = UnitRowData->Health;
	this->Damage = UnitRowData->Damage;
	this->Description = UnitRowData->Description;
	this->FinishSpawning(Transform);
}

void AParentUnit::BeginPlay()
{
	Super::BeginPlay();
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
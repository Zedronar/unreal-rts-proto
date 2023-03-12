#include "ParentUnit.h"

AParentUnit::AParentUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	
	if (GetWorld() && GetGameInstance())
	{
		this->DataTableSubsystem = GetGameInstance()->GetSubsystem<UDataTableSubsystem>();
	}
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
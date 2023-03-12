#pragma once

#include "../DataTableSubsystem.h"
#include "UnitData.h"
#include "EUnitNames.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentUnit.generated.h"

UCLASS()
class RTS_GAME_API AParentUnit : public ACharacter
{
	GENERATED_BODY()

public:
	AParentUnit();

	void Init(TSubclassOf<AParentUnit> Subclass, FTransform Transform, int32 TeamNumber, FLinearColor TeamColor, int32 StartingLevel = 1);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetupTeamColor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	EUnitNames UnitName = EUnitNames::ResourceTruck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UTexture2D* Image2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	FLinearColor TeamColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UMeshComponent*> MeshesForTeamColoring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	float Speed = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	float BuildTime = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	int32 Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FromDataTable", meta = (ExposeOnSpawn="true"))
	FString Description = "PLACEHOLDER";

private:
	UPROPERTY()
	UDataTableSubsystem* DataTableSubsystem = nullptr;
};

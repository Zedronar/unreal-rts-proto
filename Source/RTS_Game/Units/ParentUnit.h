#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParentUnit.generated.h"

UCLASS()
class RTS_GAME_API AParentUnit : public ACharacter
{
	GENERATED_BODY()

public:
	AParentUnit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// TODO: TypeName

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UTexture2D* Image2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn="true"))
	FLinearColor TeamColor;

	// TODO: Am I using this one?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float ProductionTime = 0.0;

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
};

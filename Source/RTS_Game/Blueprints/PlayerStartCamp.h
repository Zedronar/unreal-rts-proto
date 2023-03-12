#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStartCamp.generated.h"

UCLASS()
class RTS_GAME_API APlayerStartCamp : public AActor
{
	GENERATED_BODY()
	
public:
	APlayerStartCamp();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CameraLocationStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BuildingLocationStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UBoxComponent*> StartingUnits;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

private:
    UPROPERTY()
    UBoxComponent* UnitStartA;

	UPROPERTY()
	UBoxComponent* UnitStartB;

	UPROPERTY()
	UBoxComponent* UnitStartC;
};

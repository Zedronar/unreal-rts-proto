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
	UBoxComponent* UnitStartA;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* UnitStartB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* UnitStartC;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;
};

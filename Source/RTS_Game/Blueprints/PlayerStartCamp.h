#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStartCamp.generated.h"

UCLASS()
class RTS_GAME_API APlayerStartCamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStartCamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

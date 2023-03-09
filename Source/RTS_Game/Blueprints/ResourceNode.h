#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceNode.generated.h"

UCLASS()
class RTS_GAME_API AResourceNode : public AActor
{
	GENERATED_BODY()

public:
	AResourceNode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};

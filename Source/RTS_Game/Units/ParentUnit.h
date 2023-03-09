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
};

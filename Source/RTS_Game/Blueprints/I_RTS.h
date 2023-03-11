#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_RTS.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UI_RTS : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_GAME_API II_RTS
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IncrementResourceAmount(const int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClientShowNotEnoughResources();

	/*UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void ProduceUnit();*/
};

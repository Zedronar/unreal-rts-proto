#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Resource.generated.h"

UINTERFACE(MinimalAPI)
class UResource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_GAME_API IResource
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetIsWorking(AActor* ResourceNode);	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetNotWorking();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Collect();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dropoff();
};

#pragma once


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Interface.h"
#include "Tooltip.generated.h"

UINTERFACE(MinimalAPI)
class UTooltip : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_GAME_API ITooltip
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTooltip(UUserWidget* TooltipWidget);
};

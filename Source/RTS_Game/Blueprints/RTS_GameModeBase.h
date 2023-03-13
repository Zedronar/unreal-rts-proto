#pragma once

#include "PlayerStartCamp.h"
#include "CameraPawn.h"
#include "../Interfaces/I_RTS.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RTS_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API ARTS_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARTS_GameModeBase();

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APlayerStartCamp*> PlayerStartCamps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerStartCamp* SelectedPlayerStartCamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TeamNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> TeamColors = { FLinearColor::Blue , FLinearColor::Red, FLinearColor::Green, FLinearColor::Yellow};
};

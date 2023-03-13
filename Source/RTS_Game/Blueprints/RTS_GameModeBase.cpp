#include "RTS_GameModeBase.h"

ARTS_GameModeBase::ARTS_GameModeBase()
{
	// Get all player start camps from world
	TArray<AActor*> OutActors = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStartCamp::StaticClass(), OutActors);
	PlayerStartCamps = reinterpret_cast<const TArray<APlayerStartCamp*>&>(OutActors);
}

void ARTS_GameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// Select a random player start camp
	SelectedPlayerStartCamp = PlayerStartCamps[FMath::RandRange(0, PlayerStartCamps.Num() - 1)];
	
	// Spawn camera pawn
	ACameraPawn* NewCameraPawn = GetWorld()->SpawnActor<ACameraPawn>(
		ACameraPawn::StaticClass(),
		SelectedPlayerStartCamp->CameraLocationStart->GetComponentTransform()
	);
	NewPlayer->Possess(NewCameraPawn);

	// Send player starting info to player controller
	II_RTS::Execute_SetupPlayerStart(NewPlayer, SelectedPlayerStartCamp, TeamNumber, TeamColors[TeamNumber]);

	// Increment team number and remove player start camp
	TeamNumber++;
	PlayerStartCamps.Remove(SelectedPlayerStartCamp);
}

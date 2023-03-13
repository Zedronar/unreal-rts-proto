#include "ResourceNode.h"

AResourceNode::AResourceNode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceNode::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceNode::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (this->HasAuthority())
	{
		// Cast to interface
		if (OtherActor->GetClass()->ImplementsInterface(UResource::StaticClass()))
		{
			// Call Collect function if actor implements interface
			IResource::Execute_Collect(OtherActor);
		}
	}
}

void AResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

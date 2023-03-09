#include "ResourceNode.h"

AResourceNode::AResourceNode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AResourceNode::BeginPlay()
{
	Super::BeginPlay();
}

void AResourceNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBuildingNames.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBuildingNames : uint8
{
	CommandCenter = 0 UMETA(DisplayName = "CommandCenter"),
	CarFactory = 1 UMETA(DisplayName = "CarFactory"),
	Hangar = 2 UMETA(DisplayName = "Hangar"),
    Max UMETA(Hidden),
};
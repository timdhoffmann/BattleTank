// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Should be first include.
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
// Must be the last include!
#include "TankTurret.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"// Must be the last include!

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSecond) const;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationSpeedDegreesPerSecond = 20.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 35.0f;
};

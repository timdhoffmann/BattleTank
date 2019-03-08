// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"// Must be the last include!

#pragma region Forward Declarations
class UWorld;
#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/// Elevates the barrel.
	/// -1 is max downward speed, +1 is max upward speed.
	void RotatePitch(float AxisRelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxRotationSpeedDegreesPerSecond = 5.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinPitchAngle = 0.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxPitchAngle = 35.0f;
};

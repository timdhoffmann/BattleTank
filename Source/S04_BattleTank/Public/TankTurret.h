// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once
// Should be first include.
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
// Must be the last include!
#include "TankTurret.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	/// Elevates the barrel.
	/// -1 is max clockwise speed, +1 is max counter-clockwise speed.
	void RotateYaw(float AxisRelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxRotationSpeedDegreesPerSecond = 20.f;
};

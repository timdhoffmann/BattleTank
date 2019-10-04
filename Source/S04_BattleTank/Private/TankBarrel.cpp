// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankBarrel.h"
#include "Engine/World.h"

// Applies the pitch rotation, this frame, to barrel.
// Taking into account max elevation speed and this frame time.
void UTankBarrel::RotatePitch(float AxisRelativeSpeed)
{
	AxisRelativeSpeed = FMath::Clamp(AxisRelativeSpeed, -1.f, 1.f);

	const auto DeltaPitch = AxisRelativeSpeed * MaxRotationSpeedDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	const auto NewPitch = FMath::Clamp(RelativeRotation.Pitch + DeltaPitch, MinPitchAngle, MaxPitchAngle);

	SetRelativeRotation(FRotator(NewPitch, 0.f, 0.f));

	const auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("[%f] Rotating pitch at: %f degrees per second"), Time, AxisRelativeSpeed);
}
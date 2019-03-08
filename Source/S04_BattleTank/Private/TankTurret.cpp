// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

// Applies the yaw rotation, this frame, to turret.
// Taking into account max rotation speed and this frame time.
void UTankTurret::RotateYaw(float AxisRelativeSpeed)
{
	AxisRelativeSpeed = FMath::Clamp(AxisRelativeSpeed, -1.f, 1.f);

	const auto DeltaYaw = AxisRelativeSpeed * MaxRotationSpeedDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	const auto NewYaw = RelativeRotation.Yaw + DeltaYaw;

	SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));

	const auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("[%s] Rotating yaw at: %f degrees per second"), *GetOwner()->GetName(), AxisRelativeSpeed);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(const float NormalizedRelativeSpeed) const
{
	// Apply the right y-rotation-amount, this frame, to barrel.
	// Taking into account max elevation speed and this frame time.

	/*const auto RotationSpeed = 2.0f;
	Barrel->AddLocalRotation(DeltaRotator * RotationSpeed * FApp::GetDeltaTime());*/

	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("[%f] Elevating at: %f degrees per second"), Time, NormalizedRelativeSpeed);
}
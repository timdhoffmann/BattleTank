// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond) const
{
	// Apply the right y-rotation-amount, this frame, to barrel.
	// Taking into account max elevation speed and this frame time.

	/*const auto RotationSpeed = 2.0f;
	Barrel->AddLocalRotation(DeltaRotator * RotationSpeed * FApp::GetDeltaTime());*/

	UE_LOG(LogTemp, Warning, TEXT("Elevating at: %f degrees per second"), DegreesPerSecond);
}
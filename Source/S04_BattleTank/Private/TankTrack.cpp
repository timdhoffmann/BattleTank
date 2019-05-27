// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(const float Throttle) const
{
	// TODO: Clamp throttle value between -1 and 1.

	// TODO: Implement movement.

	const auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;

	auto TankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRootComponent->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
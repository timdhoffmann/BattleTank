// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankTrack.h"

void UTankTrack::SetThrottle(const float Throttle) const
{
	// TODO: Clamp throttle value between -1 and 1.

	const auto Name = GetName();

	const auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;

	auto TankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRootComponent->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
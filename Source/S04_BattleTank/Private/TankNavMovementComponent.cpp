// Fill out your copyright notice in the Description page of Project Settings.

#include "TankNavMovementComponent.h"
#include "TankTrack.h"

void UTankNavMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (ensure(LeftTrackToSet != nullptr) && ensure(RightTrackToSet != nullptr))
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

void UTankNavMovementComponent::IntendMoveForward(const float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Indend move forward throw: %f"), Throw);

	// TODO: Prevent double-speed when using multiple input devices.
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}
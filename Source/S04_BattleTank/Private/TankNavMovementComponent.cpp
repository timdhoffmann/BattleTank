// Fill out your copyright notice in the Description page of Project Settings.

#include "TankNavMovementComponent.h"
#include "TankTrack.h"

#pragma region Overrides

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super. Logic will be replaced.
    UE_LOG(LogTemp, Warning, TEXT("[%s] RequestDirectMove() velocity: %s"), *(GetOwner()->GetName()), *(MoveVelocity.ToString()));
}

#pragma endregion

void UTankNavMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    if (ensure(LeftTrackToSet != nullptr) && ensure(RightTrackToSet != nullptr))
    {
        LeftTrack = LeftTrackToSet;
        RightTrack = RightTrackToSet;
    }
}

void UTankNavMovementComponent::IntendMoveForward(const float Throw) const
{
    // TODO: Prevent double-speed when using multiple input devices.

    if (ensure(LeftTrack != nullptr && RightTrack != nullptr))
    {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(Throw);
    }
}

void UTankNavMovementComponent::IntendTurnRight(const float Throw) const
{
    // TODO: Prevent double-speed when using multiple input devices.

    if (ensure(LeftTrack != nullptr && RightTrack != nullptr))
    {
        LeftTrack->SetThrottle(Throw);
        RightTrack->SetThrottle(-Throw);
    }
}
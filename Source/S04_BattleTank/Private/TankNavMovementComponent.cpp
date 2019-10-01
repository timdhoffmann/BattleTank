// Fill out your copyright notice in the Description page of Project Settings.

#include "TankNavMovementComponent.h"
#include "TankTrack.h"

#pragma region Overrides

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super. Logic will be replaced.

	const FVector TankForwardVectorNormal = GetOwner()->GetActorForwardVector();
	// BUG: Why doesn't this get normalized?
	const auto MoveVelocityNormal = MoveVelocity.GetSafeNormal(0.0001f);
	const float ForwardThrow = FVector::DotProduct(TankForwardVectorNormal, MoveVelocityNormal);

	UE_LOG(LogTemp, Warning, TEXT("[%s] MoveVelocity: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());

	UE_LOG(LogTemp, Warning, TEXT("[%s] TankForwardVectorNormal: %s, MoveVelocityNormal: %s, ForwardThrow: %f"),
		*GetOwner()->GetName(),
		*TankForwardVectorNormal.ToString(),
		*MoveVelocityNormal.ToString(),
		ForwardThrow);

	IntendMoveForward(ForwardThrow);
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
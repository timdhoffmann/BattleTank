// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankNavMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "TankTrack.h"

#pragma region Overrides

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super. Logic will be replaced.

	const FVector TankForwardVectorNormal = GetOwner()->GetActorForwardVector();

	// TODO: Why doesn't this work when normalizing with GetSafeNormal()?
	const auto MoveVelocityNormal = MoveVelocity.GetClampedToSize(-1.0f, 1.0f);

	// Calculates the ForwardThrow.
	const float ForwardThrow = FVector::DotProduct(TankForwardVectorNormal, MoveVelocityNormal);

	// Applies the ForwardThrow.
	IntendMoveForward(ForwardThrow);

	/*UE_LOG(LogTemp, Warning, TEXT("[%s] MoveVelocity: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
	UE_LOG(LogTemp, Warning, TEXT("[%s] TankForwardVectorNormal: %s, MoveVelocityNormal: %s, ForwardThrow: %f"),
		*GetOwner()->GetName(),
		*TankForwardVectorNormal.ToString(),
		*MoveVelocityNormal.ToString(),
		ForwardThrow);
	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + MoveVelocityNormal, FColor::Magenta, false, -1, 0, 1);*/

	// Calculates the IntendTurnRight. Order of vectors matters for CrossProduct!
	const float RightThrow = FVector::CrossProduct(TankForwardVectorNormal, MoveVelocityNormal).GetClampedToSize(-1.0f, 1.0f).Z;

	// Applies the IntendTurnRight.
	IntendTurnRight(RightThrow);
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
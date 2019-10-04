// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankNavMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "TankTrack.h"

#pragma region Overrides

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super. Logic will be replaced.

	const FVector TankForwardVectorNormal = GetOwner()->GetActorForwardVector();

	// TODO: BUG! GetSafeNormal() only works in debug builds in this context! Filed to Epic.
	//const auto MoveVelocityNormal = MoveVelocity.GetSafeNormal();
	// TODO: Verify: is GetClampedToSize() leading to the same result as normalizing, here?
	const auto MoveVelocityNormal = MoveVelocity.GetClampedToSize(-1.0f, 1.0f);
	/*UE_LOG(LogTemp, Warning, TEXT("[%s] MoveVelocityNormal: %s, IsNormalized: %s"),
		*GetOwner()->GetName(),
		*MoveVelocityNormal.ToString(),
		MoveVelocityNormal.IsNormalized() ? TEXT("True") : TEXT("False"));
	*/

	//const FVector Test = FVector(2.f, 3.f, 4.f);
	//const auto TestNormal = Test.GetSafeNormal();
	////const auto MoveVelocityNormal = MoveVelocity.GetClampedToSize(-1.0f, 1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("[%s] TestNormal: %s, IsNormalized: %s"),
	//	*GetOwner()->GetName(),
	//	*TestNormal.ToString(),
	//	TestNormal.IsNormalized() ? TEXT("True") : TEXT("False"));

	// Calculates the ForwardThrow.
	const float ForwardThrow = FVector::DotProduct(TankForwardVectorNormal, MoveVelocityNormal);

	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + MoveVelocityNormal, FColor::Magenta, false, -1, 0, 1);

	// Applies the ForwardThrow.
	IntendMoveForward(ForwardThrow);

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
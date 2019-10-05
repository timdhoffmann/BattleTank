// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankTrack.h"
#include "Components/StaticMeshComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

#pragma region Overrides

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	TankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculates the sideways SlippageSpeed.
	// If the tank's velocity vector is perpendicular to the RightVector, SlippageSpeed = 0.
	// If the tank's velocity vector is parallel to the RightVector, SlippageSpeed = the tank's velocity.
	const float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Calculates the required acceleration this frame to correct.
	const FVector  CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculates and applies sideways for (F = m a).
	const auto StaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	// Halve the CorrectionForce because it will be applied to two tracks.
	const auto CorrectionForce = StaticMeshComponent->GetMass() * CorrectionAcceleration * 0.5f;

	TankRootComponent->AddForce(CorrectionForce);
}

#pragma endregion

void UTankTrack::SetThrottle(const float Throttle) const
{
	// TODO: Clamp throttle value between -1 and 1.

	const auto Name = GetName();

	const auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;

	TankRootComponent->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
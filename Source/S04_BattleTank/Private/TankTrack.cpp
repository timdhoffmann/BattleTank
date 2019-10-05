// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankTrack.h"
#include "Components/StaticMeshComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Subscribes to the OnComponentHit physics event.
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

#pragma region Overrides

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	TankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

#pragma endregion

#pragma region Event Handlers

// Event gets raised when the tank has contact with another body, e.g. the ground.
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	CompensateSidewaysSlippage();
	CurrentThrottle = 0.0f;
}

#pragma endregion

void UTankTrack::CompensateSidewaysSlippage() const
{
	// Calculates the current sideways SlippageSpeed.
	// If the tank's velocity vector is perpendicular to the RightVector, SlippageSpeed = 0.
	// If the tank's velocity vector is parallel to the RightVector, SlippageSpeed = the tank's velocity.
	const float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Calculates the required acceleration this frame to correct.
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	const FVector  CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculates and applies sideways for (F = m a).
	const auto StaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	// Halve the CorrectionForce because it will be applied to two tracks.
	const auto CorrectionForce = StaticMeshComponent->GetMass() * CorrectionAcceleration * 0.5f;

	TankRootComponent->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack() const
{
	const auto Force = GetForwardVector() * MaxDrivingForce * CurrentThrottle;
	TankRootComponent->AddForceAtLocation(Force, GetComponentLocation());
}

void UTankTrack::SetThrottle(const float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);
}
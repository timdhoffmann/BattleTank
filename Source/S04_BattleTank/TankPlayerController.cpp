// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Called when the game starts.
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const auto ControlledTank = GetControlledPawn();

	if (ensureMsgf(ControlledTank != nullptr, TEXT("No controlled tank found.")))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] found controlled pawn: %s"), *(GetName()), *(ControlledTank->GetName()));
	}

}

// Called every frame to update this actor.
void ATankPlayerController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair() const
{
	if (!GetControlledPawn())
	{
		return;
	}

	auto OutHitLocation = FVector(0.0f, 0.0f, 0.0f); // Out parameter.
	// Get world location from line trace through crosshair.
	if (GetHitLocation(OutHitLocation))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("[%s] HitLocation: %s"), *(GetName()), *(OutHitLocation.ToString()));

		// TODO: implementation:
		// If it hits the landscape.
		// Tell controlled tank to aim at this point. 
	}
}

ATank* ATankPlayerController::GetControlledPawn() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetHitLocation(FVector OutHitLocation) const
{
	/// Set up parameters used for the LineTrace.
	FHitResult OutHitResult;
	const FCollisionObjectQueryParams ObjectTypesLookedFor(ECollisionChannel::ECC_PhysicsBody);
	const FCollisionQueryParams AdditionalTraceParameters
	(
		FName(TEXT("")),	// use empty tag,
		false,				// use simplified collider,
		GetOwner()			// ignore ourselves (because the LineTrace starts in the center of our body).
	);

	// Execute LineTrace (Ray-cast).
	return GetWorld()->LineTraceSingleByObjectType
	(
		OutHitResult, 
		GetLineTraceStart(), 
		GetLineTraceEnd(), 
		ObjectTypesLookedFor, 
		AdditionalTraceParameters
	);
}

FVector ATankPlayerController::GetLineTraceStart() const
{
	// Get PlayerViewPoint data.
	FVector OutLocation;
	FRotator OutRotation;
	GetPlayerViewPoint(OutLocation, OutRotation);

	return OutLocation;
}

FVector ATankPlayerController::GetLineTraceEnd() const
{
	// Get PlayerViewPoint data.
	FVector OutLocation;
	FRotator OutRotation;
	GetPlayerViewPoint(OUT OutLocation, OUT OutRotation);

	const FVector LineTraceDirection = OutRotation.Vector(); // (Normalized) unit vector of length 1.
	const int Meters = 100;
	return OutLocation + LineTraceDirection * 10 * Meters;
}


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

	/*const FColor Color = FColor Red;

	DrawDebugLine
	(
		GetWorld(),
		GetLineTraceStart(),
		GetLineTraceEnd(10),
		Color
		);*/
}

void ATankPlayerController::AimAtCrosshair() const
{
	if (!GetControlledPawn())
	{
		return;
	}

	FVector OutHitLocation = FVector(0.0f); // Out parameter.
	if (GetCrosshairHitLocation(OutHitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] HitLocation: %s"), *(GetName()), *(OutHitLocation.ToString()));

		// TODO: If it hits the landscape...
		// Tell controlled tank to aim at this point. 
	}
}

ATank* ATankPlayerController::GetControlledPawn() const
{
	return Cast<ATank>(GetPawn());
}

// Get world location from line trace through crosshair.
bool ATankPlayerController::GetCrosshairHitLocation(FVector& OutHitLocation) const
{
	/// Set up parameters used for the LineTrace.
	const FName TraceTag("DebugViewport");
	FHitResult OutHitResult;
	const FCollisionObjectQueryParams ObjectTypesLookedFor(ECollisionChannel::ECC_PhysicsBody);
	const FCollisionQueryParams AdditionalTraceParameters
	(
		TraceTag,	// use empty tag,
		false,				// use simplified collider,
		GetOwner()			// ignore ourselves (because the LineTrace starts in the center of our body).
	);

	// Draw debug trace.
	GetWorld()->DebugDrawTraceTag = TraceTag;

	/// Execute LineTrace (Ray-cast).
	if 
	(
		GetWorld()->LineTraceSingleByObjectType
		(
			OutHitResult, GetLineTraceStart(), GetLineTraceEnd(10), ObjectTypesLookedFor, AdditionalTraceParameters
		)
	)
	{
		OutHitLocation = OutHitResult.ImpactPoint;
		return true;
	}
	return false;
	// TODO: Does this happen?: 
	// 1. Find crosshair position. 
	// 2. De-project screen position of crosshair to a world direction. 
	// 3. Line trace along that look direction and see what we hit.
}

// Gets the start of the line trace.

inline FVector ATankPlayerController::GetLineTraceStart() const
{
	// Get PlayerViewPoint data.
	FVector OutLocation;
	FRotator OutRotation;
	GetPlayerViewPoint(OutLocation, OutRotation);

	return OutLocation;
}

FVector ATankPlayerController::GetLineTraceEnd(const int32 MaxRangeMeters) const
{
	// Get PlayerViewPoint data.
	FVector OutLocation;
	FRotator OutRotation;
	GetPlayerViewPoint(OutLocation, OutRotation);

	const FVector LineTraceDirection = OutRotation.Vector(); // (Normalized) unit vector of length 1.
	return OutLocation + LineTraceDirection * MaxRangeMeters * 100;
}


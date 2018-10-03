// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#pragma region Overrides
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
#pragma endregion


void ATankPlayerController::AimAtCrosshair() const
{
	if (!GetControlledPawn())
	{
		return;
	}

	auto OutHitLocation = FVector(0.0f); // Out parameter.
	if (GetCrosshairHitLocation(OutHitLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("[%s] HitLocation: %s"), *(GetName()), *(OutHitLocation.ToString()));

		// TODO: If it hits the landscape...
		// Tell controlled tank to aim at this point. 
	}
}

#pragma region Getters
ATank* ATankPlayerController::GetControlledPawn() const
{
	return Cast<ATank>(GetPawn());
}

// Get world location from line trace through crosshair.
bool ATankPlayerController::GetCrosshairHitLocation(FVector& OutHitLocation) const
{
	// TODO: Does this happen?:
	// 1. Find crosshair position in pixel coordinates. 
	// 2. De-project screen position of crosshair to a world direction. 
	// 3. Line trace along that look direction and see what we hit.

	FVector OutAimDirectionUnitVector, OutCrosshairWorldLocation;
	// Get aim direction unit vector.
	if (GetAimDirectionThroughCrosshair(OutAimDirectionUnitVector,OutCrosshairWorldLocation))
	{
		return GetAimDirectionHitLocation(OutHitLocation, OutCrosshairWorldLocation, OutAimDirectionUnitVector);

	}
	return false;
}

bool ATankPlayerController::GetAimDirectionThroughCrosshair(FVector& OutAimDirectionUnitVector, FVector& OutCrosshairWorldLocation) const
{
	int32 OutViewportSizeX, OutViewportSizeY;
	GetViewportSize(OutViewportSizeX, OutViewportSizeY);

	// Calculates CrosshairScreenPosition in pixel coordinates.
	const auto CrosshairScreenPosition = FVector(OutViewportSizeX * CrosshairXLocation, OutViewportSizeY * CrosshairYLocation, 0.0f);

	// De-projects screen position to world coordinates.
	return DeprojectScreenPositionToWorld
	(
		CrosshairScreenPosition.X,
		CrosshairScreenPosition.Y,
		OutCrosshairWorldLocation,
		OutAimDirectionUnitVector
	);
}

bool ATankPlayerController::GetAimDirectionHitLocation(FVector& OutHitLocation, const FVector LineTraceStart, const FVector LineTraceDirection) const
{
	/// Set up arguments used for the LineTrace.
	FHitResult OutHitResult;
	const ECollisionChannel ObjectTypesLookedFor(ECollisionChannel::ECC_PhysicsBody);
	const FName TraceTag("DebugViewport");
	const FCollisionQueryParams AdditionalTraceParameters
	(
		TraceTag, // tag to identify the line trace,
		false, // use simplified collider,
		GetOwner() // ignore ourselves (because the LineTrace starts in the center of our body).
	);

	/// Execute LineTrace (Ray-cast).
	if
	(
		GetWorld()->LineTraceSingleByChannel
		(
			OutHitResult, LineTraceStart, LineTraceDirection * AimLineTraceRangeKm * 1e5, ObjectTypesLookedFor, AdditionalTraceParameters
		)
	)
	{
		OutHitLocation = OutHitResult.ImpactPoint;

		// Draw debug trace.
		GetWorld()->DebugDrawTraceTag = TraceTag;
		UE_LOG(LogTemp, Warning, TEXT("Hitresult: %s"), *OutHitResult.Actor->GetName());

		return true;
	}
	return false;
}

// Gets the start of the line trace.
FVector ATankPlayerController::GetLineTraceStart() const
{
	// TODO: Implementation.

	return FVector();
}

FVector ATankPlayerController::GetLineTraceEnd(const int32 MaxRangeMeters) const
{
	// TODO: Implementation.

	return FVector();
}
#pragma endregion

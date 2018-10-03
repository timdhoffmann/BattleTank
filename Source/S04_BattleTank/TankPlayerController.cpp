// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#pragma region Overrides
// Called when the game starts.
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledPawn();

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
#pragma endregion


void ATankPlayerController::AimAtCrosshair() const
{
	ensure(ControlledTank);

	auto HitLocation = FVector(0.0f); // Out parameter.
	if (GetCrosshairHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
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

	// Get aim direction unit vector.
	FVector AimDirectionUnitVector;
	if (GetAimDirectionThroughCrosshair(AimDirectionUnitVector))
	{
		// Line traces along aim direction unit vector up to max range and looks for whats being hit.
		return GetAimDirectionHitLocation(OutHitLocation, AimDirectionUnitVector);
	}
	return false;
}

bool ATankPlayerController::GetAimDirectionThroughCrosshair(FVector& OutAimDirectionUnitVector) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Calculates CrosshairScreenPosition in pixel coordinates.
	const auto CrosshairScreenPosition = FVector
	(
		ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation, 0.0f
	);

	// De-projects screen position to world coordinates.
	auto CrosshairWorldLocation = FVector(0.0f);
	return DeprojectScreenPositionToWorld
	(
		CrosshairScreenPosition.X,
		CrosshairScreenPosition.Y,
		CrosshairWorldLocation,
		OutAimDirectionUnitVector
	);
}

bool ATankPlayerController::GetAimDirectionHitLocation(FVector& OutHitLocation, const FVector LineTraceDirection) const
{
	/// Set up arguments used for the LineTrace.
	FHitResult HitResult;
	const auto LineTraceStart = PlayerCameraManager->GetCameraLocation();
	const auto LineTraceEnd = LineTraceStart + LineTraceDirection * AimLineTraceRangeKm * 1e5;
	const ECollisionChannel ObjectTypesLookedFor(ECollisionChannel::ECC_PhysicsBody);

	const FName TraceTag("DebugViewport");
	const auto UseSimplifiedCollider = false;
	const AActor* ActorToIgnore = GetOwner(); // Ourselves (because the LineTrace starts in the center of our body).
	const FCollisionQueryParams AdditionalTraceParameters(TraceTag, UseSimplifiedCollider, ActorToIgnore);

	/// Execute LineTrace (Ray-cast).
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult, LineTraceStart, LineTraceEnd, ObjectTypesLookedFor, AdditionalTraceParameters
			)
	)
	{
		OutHitLocation = HitResult.ImpactPoint;

		return true;
	}
	return false;
}
#pragma endregion

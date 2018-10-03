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
		// UE_LOG(LogTemp, Warning, TEXT("[%s] HitLocation: %s"), *(GetName()), *(OutHitLocation.ToString()));

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
	// TODO: Does this happen?: 
	// 1. Find crosshair position in pixel coordinates. 
	// 2. De-project screen position of crosshair to a world direction. 
	// 3. Line trace along that look direction and see what we hit.
	
	/// Finds crosshair position in pixel coordinates.
	int32 OutViewportSizeX, OutViewportSizeY;
	GetViewportSize(OutViewportSizeX, OutViewportSizeY);
	const auto CrosshairScreenLocation = FVector(OutViewportSizeX * CrosshairXLocation, OutViewportSizeY * CrosshairYLocation, 0.0f);

	/// De-projects screen position to world coordinates.
	// Set up out parameters.
	FVector OutWorldLocation, OutWorldDirection;
	if (DeprojectScreenPositionToWorld(CrosshairScreenLocation.X, CrosshairScreenLocation.Y, OutWorldLocation,	OutWorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("OutWorldDirection: %s"), *(OutWorldDirection.ToString()));
	}

	
	/// Set up parameters used for the LineTrace.
	const FName TraceTag("DebugViewport");
	FHitResult OutHitResult;
	const FCollisionObjectQueryParams ObjectTypesLookedFor(ECollisionChannel::ECC_PhysicsBody);
	const FCollisionQueryParams AdditionalTraceParameters
	(
		TraceTag, // use empty tag,
		false, // use simplified collider,
		GetOwner() // ignore ourselves (because the LineTrace starts in the center of our body).
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


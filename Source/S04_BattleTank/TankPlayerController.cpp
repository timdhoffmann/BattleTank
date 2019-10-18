// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

#pragma region Overrides
// Called when the game starts.
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensureMsgf(AimingComponent != nullptr, TEXT("No aiming component found.")))
	{
		FoundAimingComponent(AimingComponent);
	}
}

// Called every frame to update this actor.
void ATankPlayerController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimAtCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn == nullptr)
	{
		return;
	}

	auto PossessedTank = Cast<ATank>(InPawn);

	if (!ensure(PossessedTank != nullptr))
	{
		return;
	}

	PossessedTank->OnDied.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDied);
}
#pragma endregion

void ATankPlayerController::AimAtCrosshair() const
{
	auto HitLocation = FVector(0.0f); // Out parameter.
	if (GetCrosshairHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

#pragma region Getters

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
	const auto CrosshairScreenPosition = FVector(
		ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation, 0.0f);

	// De-projects screen position to world coordinates.
	auto CrosshairWorldLocation = FVector(0.0f);
	return DeprojectScreenPositionToWorld(
		CrosshairScreenPosition.X,
		CrosshairScreenPosition.Y,
		CrosshairWorldLocation,
		OutAimDirectionUnitVector);
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
		HitResult, LineTraceStart, LineTraceEnd, ObjectTypesLookedFor, AdditionalTraceParameters))
	{
		OutHitLocation = HitResult.ImpactPoint;

		return true;
	}
	return false;
}

#pragma endregion

#pragma region Delegate & Event Subsribers

void ATankPlayerController::OnPossessedTankDied()
{
	// Enables spectator mode.
	StartSpectatingOnly();
	
	UE_LOG(LogTemp, Warning, TEXT("Player died!"));
}

#pragma endregion
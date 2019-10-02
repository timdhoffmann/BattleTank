// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include!

#pragma region Forward Declarations
class UTankAimingComponent;
class ATank;
#pragma endregion

/**
 * Controls a tank.
 */
UCLASS()
class S04_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

#pragma region Variables

private:

	/// Variables:
	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
		int32 AimLineTraceRangeKm = 10;

	// The Tank controlled by the player.
	const ATank* ControlledTank = nullptr;

#pragma endregion

#pragma region Functions

protected:

	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank* GetControlledTank() const;

	// Raises an event in blueprint when the aiming component was found.
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent* TankAimingComponentRef); // Needs no definition as a BlueprintImplementableEvent.

private:

	// Called when the game starts.
	virtual void BeginPlay() override;

	// Called every frame to update this actor.
	virtual void Tick(float DeltaSeconds) override;

	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world.
	void AimAtCrosshair() const;

	// Gets a unit vector in the direction where the crosshair is pointing.
	// Returns true on success.
	bool GetAimDirectionThroughCrosshair(FVector& OutAimDirectionUnitVector) const;

	/// Gets the world location hit from line trace through the crosshair and stores it in the out parameter.
	/// Returns true if hit landscape.
	// TODO: Check condition for returning true.
	bool GetCrosshairHitLocation(FVector& OutHitLocation) const;

	// Performs a line trace and stores the hit location in the out parameter.
	// Returns false if nothing was hit.
	bool GetAimDirectionHitLocation(FVector& OutHitLocation, const FVector LineTraceDirection) const;

#pragma endregion
};

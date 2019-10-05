// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Moves the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

#pragma region Functions

public:

	// Sets the throttle on a single track.
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(const float Throttle);

private:

	UTankTrack();

	virtual void BeginPlay() override;

	// Compensates for the sideways slippage of the moving tank.
	void CompensateSidewaysSlippage() const;
	void DriveTrack() const;

	// Delegate to be called by the OnComponentHit physics event.
	// Must be a UFUNCTION.
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion

#pragma region Variables

private:

	// Max force per track in Newtons.
	// Assume 40t tank, 1g acceleration.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDrivingForce = 400000.f;

	float CurrentThrottle = 0.0f;

	UPrimitiveComponent* TankRootComponent;

#pragma endregion
};

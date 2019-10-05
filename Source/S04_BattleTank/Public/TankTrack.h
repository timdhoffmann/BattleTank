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
		void SetThrottle(float Throttle) const;

private:

	UTankTrack();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Variables

private:

	// Max force per track in Newtons.
	// Assume 40t tank, 1g acceleration.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDrivingForce = 400000.f;

	UPrimitiveComponent* TankRootComponent;

#pragma endregion
};

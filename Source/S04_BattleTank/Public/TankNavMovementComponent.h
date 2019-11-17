// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankNavMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank with its tracks.
 */
UCLASS(ClassGroup = Custom, meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API UTankNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

#pragma region Variables

private:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

#pragma endregion

#pragma region Functions

public:

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw) const;

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw) const;

private:

	// Requests a new velocity from the AIController path finding logic.
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

#pragma endregion
};

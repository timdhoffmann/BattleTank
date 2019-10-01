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

public:

#pragma region Functions

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw) const;

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw) const;

#pragma endregion

private:

#pragma region Functions

	// Requests a new velocity from the AIController path finding logic.
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

#pragma endregion

#pragma region Variables

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

#pragma endregion
};

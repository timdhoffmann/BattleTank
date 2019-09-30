// Fill out your copyright notice in the Description page of Project Settings.

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

	// TODO: Check best protection.
	// Requests a new velocity.
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw) const;

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw) const;

#pragma endregion

private:

#pragma region Variables

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

#pragma endregion
};

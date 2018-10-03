// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Camera/PlayerCameraManager.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include!

/**
 * 
 */
UCLASS()
class S04_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/// Functions:
	// Called when the game starts.
	virtual void BeginPlay() override;
	
	// Called every frame to update this actor.
    virtual void Tick(float DeltaSeconds) override;
	
private:
	/// Variables:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

	/// Functions:
	ATank* GetControlledPawn() const;

	/// Gets the world location hit from line trace through the crosshair and stores it in the out parameter.
	/// Returns true if hit landscape. 
	// TODO: Check condition for returning true.
	bool GetCrosshairHitLocation(FVector& OutHitLocation) const;

	// Gets the start of the line trace.
	FVector GetLineTraceStart() const;
	
	// Gets the end of the line trace in MaxRangeMeters distance.
	FVector GetLineTraceEnd(int32 MaxRangeMeters) const;

	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world.
	void AimAtCrosshair() const;
};

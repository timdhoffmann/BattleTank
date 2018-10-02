// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
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
	/// Functions.
	ATank* GetControlledPawn() const;
};

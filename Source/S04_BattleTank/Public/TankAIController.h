// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class S04_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	/// Functions:
	// Called when the game starts.
	void BeginPlay() override;
	
private:
	/// Functions:
	// Gets the tank, this controller is controlling.
	ATank* GetControlledPawn() const;

	// Gets the tank controlled by the player.
	ATank* GetPlayerPawn() const;
};

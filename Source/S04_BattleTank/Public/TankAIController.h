// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class S04_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	/// Functions.

	// Called when the game starts.
	void BeginPlay() override;

	// Gets the tank, this controller is controlling.
	ATank* GetControlledTank() const;
};

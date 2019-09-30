// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

#pragma region Forward Declarations
class ATank;
#pragma endregion

/**
 *
 */
UCLASS()
class S04_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	// How close can the AI get to the player.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadiusCm = 300.0f;

#pragma region Functions
	// Called when the game starts.
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
#pragma endregion
};

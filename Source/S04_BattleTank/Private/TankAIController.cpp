// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

// Called when the game starts.
void ATankAIController::BeginPlay()
{
	auto ControlledTank = GetControlledPawn();
	if (ensureMsgf(ControlledTank != nullptr, TEXT("No controlled pawn found.")))
	{
	}

	auto PlayerTank = GetPlayerPawn();
	if (ensureMsgf(PlayerTank != nullptr, TEXT("No player pawn found.")))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] found player controlled pawn [%s]"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
	}
}

/// Gets the tank controlled by this object.
ATank* ATankAIController::GetControlledPawn() const
{
	return Cast<ATank>(GetPawn());
}

/// Gets the tank controlled by the player.
ATank * ATankAIController::GetPlayerPawn() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	return Cast<ATank>(PlayerPawn);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

// Called when the game starts.
void ATankAIController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();

	if (ensureMsgf(ControlledTank != nullptr, TEXT("No controlled tank found.")))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controlled tank: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	
	return Cast<ATank>(GetPawn());
}

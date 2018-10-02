// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledPawn();

	if (ensureMsgf(ControlledTank != nullptr, TEXT("No controlled tank found.")))
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] found controlled pawn: %s"), *(GetName()), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledPawn() const
{
	return Cast<ATank>(GetPawn());
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

#pragma region Overrides

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank != nullptr)
	{
		ATank* ControlledTank = Cast<ATank>(GetPawn());
		ensure(ControlledTank != nullptr);

		//TODO: Move towards the player.

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//TODO: Limit fire rate.
		ControlledTank->Fire();
	}
}
#pragma endregion
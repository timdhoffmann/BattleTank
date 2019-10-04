// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
// Depends on movement component via NavMesh AI system.

#pragma region Overrides

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (ensure(PlayerTank != nullptr))
    {
        ATank* ControlledTank = Cast<ATank>(GetPawn());
        ensure(ControlledTank != nullptr);

        // Moves towards the player. Needs AcceptanceRadius!
        MoveToActor(PlayerTank, AcceptanceRadiusCm);

        // Aims at the player.
        ControlledTank->AimAt(PlayerTank->GetActorLocation());

        //TODO: Limit fire rate.
        ControlledTank->Fire();
    }
}
#pragma endregion
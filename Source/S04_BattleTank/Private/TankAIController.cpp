// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
// Depends on movement component via NavMesh AI system.

#pragma region Overrides

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ensure(AimingComponent != nullptr);

	Target = GetWorld()->GetFirstPlayerController()->GetPawn();
	ensureMsgf(Target != nullptr, TEXT("Couldn't find a reference to the player."));
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Target != nullptr)
	{
		// Moves towards the player. Needs AcceptanceRadius!
		MoveToActor(Target, AcceptanceRadiusCm);

		// Aims at the player.
		AimingComponent->AimAt(Target->GetActorLocation());

		// TODO: Limit fire rate.
		if (AimingComponent->GetAimState() == EAimState::Locked)
		{
			AimingComponent->Fire();
		}
	}
}
#pragma endregion
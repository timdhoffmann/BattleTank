// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
// Depends on movement component via NavMesh AI system.

#pragma region Overrides

void ATankAIController::OnPossessedTankDied()
{
	APawn* Pawn = GetPawn();
	if (Pawn != nullptr)
	{
		// Stops the Tank from firing.
		// Might not be needed, when the Tank is destroying itself.
		Pawn->DetachFromControllerPendingDestroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Tank died."));
}

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

// Event subscriptions go here, because we need to make sure we have a pawn (avoid race conditions).
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn == nullptr)
	{
		return;
	}

	ATank* PossessedTank = Cast<ATank>(InPawn);

	// Can be a non-tank, e.g. a mortar.
	if (PossessedTank == nullptr)
	{
		return;
	}

	// Subscribes to OnDied event.
	PossessedTank->OnDied.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDied);
}

#pragma endregion
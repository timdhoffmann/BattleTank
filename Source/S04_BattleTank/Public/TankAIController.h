// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

#pragma region Forward Declarations
class UTankAimingComponent;
#pragma endregion

/**
 *
 */
UCLASS()
class S04_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

#pragma region Variables

private:
	// How close can the AI get to the player.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadiusCm = 4500.0f;

	UTankAimingComponent* AimingComponent = nullptr;
	AActor* Target = nullptr;

#pragma endregion

#pragma region Functions

public:
#pragma region Delegate & Event Subscribers

	// Need to be UFUNCTION()s.
	// TODO: Check accessibility level.
	UFUNCTION()
		void OnTankDied();

#pragma endregion

private:
	// Called when the game starts.
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;

#pragma endregion
};

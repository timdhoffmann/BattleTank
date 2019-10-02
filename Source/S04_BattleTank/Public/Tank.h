// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

#pragma region Forward Declarations
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
#pragma endregion

// A Tank that can be controlled by a player or by the AI.
UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

#pragma region Variables

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firing)
		float LaunchSpeed = 4e3f;

protected:

	// The Component responsible for aiming.
	UPROPERTY(BlueprintReadOnly, Category = Setup)
		UTankAimingComponent* TankAimingComponent = nullptr;

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTimeSeconds = 3.0f;

	float LastFireTime = 0.0f;

#pragma endregion

#pragma region Functions

public:

	// Aims at a target location.
	void AimAt(const FVector TargetLocation) const;

	UFUNCTION(BlueprintCallable, Category = Input)
		void Fire();

private:

	// Sets default values for this pawn's properties. Can be private in UE4!
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion
};

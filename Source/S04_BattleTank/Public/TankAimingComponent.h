// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h" // Must be the last include.

#pragma region Forward Declarations
class UTankBarrel;
#pragma endregion

/// Responsible for handling a tank's aiming.
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Functions
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(class UTankTurret* TurretToSet);
	// Aims at a target location.
	void AimAt(const FVector TargetLocation, const float LaunchSpeed) const;
	void Fire() const;
#pragma endregion

private:
#pragma region Variables
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
#pragma endregion

#pragma region Functions
	void RotateTurretAndBarrelTowards(FVector Direction) const;
#pragma endregion
};

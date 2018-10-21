// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.

#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"

#include "TankAimingComponent.generated.h" // Must be the last include.

#pragma region Forward Declarations
class UTankBarrel;
#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
#pragma region Functions
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// TODO: Add SetTurretReference().

	// Aims at a target location.
	void AimAt(const FVector TargetLocation, const float LaunchSpeed) const;
#pragma endregion

private:
#pragma region Variables
	UTankBarrel* Barrel = nullptr;
#pragma endregion

#pragma region Functions
	void RotateBarrelTowards(FVector Direction) const;
#pragma endregion
};

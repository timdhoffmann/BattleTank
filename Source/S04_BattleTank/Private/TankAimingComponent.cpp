// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	ensureMsgf(Barrel != nullptr, TEXT("Barrel reference not found."));
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	ensureMsgf(Turret != nullptr, TEXT("Turret reference not found."));
}

void UTankAimingComponent::AimAt(const FVector TargetLocation, const float LaunchSpeed) const
{
	ensureMsgf(Barrel != nullptr, TEXT("Barrel is nullptr."));

	/// Set up of arguments for SuggestProjectileVelocity().
	// Initializes OutLaunchVelocity to 0.
	FVector OutLaunchVelocity(0);
	const FVector StartLocation = Barrel->GetSocketLocation("ProjectileStart");
	const auto ActorsToIgnore = TArray<AActor*>();
	const auto bDrawDebug = false;

	// Calculates the suggested projectile velocity.
	const bool bHasProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		bDrawDebug
	);

	if (bHasProjectileVelocity)
	{
		// Stores normalized version of the suggested LaunchVelocity.
		auto const AimDirection = OutLaunchVelocity.GetSafeNormal();

		const auto ParentActorName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("[%s] Aiming from BarrelLocation: %s to TargetLocation: %s. SuggestedLaunchVelocity: %s"), *ParentActorName, *StartLocation.ToString(), *TargetLocation.ToString(), *AimDirection.ToString());

		RotateTurretAndBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::RotateTurretAndBarrelTowards(FVector Direction) const
{
	/// Rotates the barrel (pitch).
	// Uses barrel for pitch rotation.
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto DeltaRotator = Direction.Rotation() - BarrelRotator;

	// Translates AimDirection into pitch.
	Barrel->RotatePitch(DeltaRotator.Pitch);

	/// Rotates the Turret (yaw).
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateYaw(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->RotateYaw(-DeltaRotator.Yaw);
	}
}
// Copyright Tim Hoffmann (@timdhoffmann).

#include "Tank.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankNavMovementComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	//Doesn't need to tick every frame.
	PrimaryActorTick.bCanEverTick = false;
}

#pragma region Overrides

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Is this necessary? Maybe the entire BeginPlay() can be deleted?
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	ensureMsgf(TankAimingComponent != nullptr, TEXT("No reference to a UTankAimingComponent found!"));
}
#pragma endregion

void ATank::AimAt(const FVector TargetLocation) const
{
	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::Fire()
{
	// Barrel reference for spawning projectile.
	UTankBarrel* Barrel = TankAimingComponent->GetBarrel();
	ensure(Barrel != nullptr);
	const bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeSeconds;

	if (Barrel != nullptr && bIsReloaded)
	{
		// Spawns a Projectile.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation("ProjectileStart"),
			Barrel->GetSocketRotation("ProjectileStart")
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
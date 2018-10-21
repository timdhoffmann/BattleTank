// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
	ensureMsgf(Barrel != nullptr, TEXT("Barrel reference not found."));
}

void UTankAimingComponent::AimAt(const FVector TargetLocation, const float LaunchSpeed) const
{
	ensureMsgf(Barrel != nullptr, TEXT("Barrel is nullptr."));

	/// Set up of arguments for SuggestProjectileVelocity().
	// Initializes OutLaunchVelocity to 0.
	FVector OutLaunchVelocity(0);
	const FVector StartLocation = Barrel->GetSocketLocation("ProjectileStart");
	const auto ActorsToIgnore = TArray<AActor*>();

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
		false
	);

	if (bHasProjectileVelocity)
	{
		// Stores normalized version of the suggested LaunchVelocity.
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		const FString ParentActorName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("[%s] Aiming from BarrelLocation: %s to TargetLocation: %s. SuggestedLaunchVelocity: %s"), *ParentActorName, *StartLocation.ToString(), *TargetLocation.ToString(), *AimDirection.ToString());

		RotateBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::RotateBarrelTowards(FVector Direction) const
{
	// TODO: Rotate barrel.
		// Use barrel for yaw (y-rotation).
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto DeltaRotator = Direction.Rotation() - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator : %s"), *DeltaRotator.ToString());

	// Translate AimDirection into y-rotation.

	// Apply the right y-rotation-amount, this frame, to barrel.
	// Taking into account max elevation speed and this frame time.
	const auto RotationSpeed = 2.0f;
	Barrel->AddLocalRotation(DeltaRotator * RotationSpeed * FApp::GetDeltaTime());

	// Use turret for pitch (z-rotation).
	// Translate AimDirection into z-rotation.
	// Apply z-toration to turret.
}
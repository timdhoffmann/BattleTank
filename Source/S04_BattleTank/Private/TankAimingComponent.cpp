// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;
}

#pragma region Overrides

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Prevents firing before an initial reload.
	LastFireTime = GetWorld()->GetTimeSeconds();

	ensureMsgf(ProjectileBP != nullptr, TEXT("Assign a ProjectileBP in the editor."));
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	// Checks if is ready to fire.
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeSeconds)
	{
		AimState = EAimState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimState = EAimState::Aiming;
	}
	else
	{
		AimState = EAimState::Locked;
	}
}

#pragma endregion

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel != nullptr))
	{
		return false;
	}
	// TODO: BUG! Normalization seems to be unreliable in development build! Using Rotators instead. Needs refinement!
	const FRotator AimBarrelDeltaRotator = Barrel->GetForwardVector().Rotation() - AimDirectionNormal.Rotation();
	return !(AimBarrelDeltaRotator.IsNearlyZero(0.1f));
}

void UTankAimingComponent::InitReferences(UTankBarrel* BarrelReference, UTankTurret* TurretReference)
{
	if (ensureMsgf(BarrelReference != nullptr, TEXT("Barrel reference not found.")))
	{
		Barrel = BarrelReference;
	}

	if (ensureMsgf(TurretReference != nullptr, TEXT("Turret reference not found.")))
	{
		Turret = TurretReference;
	}
}

void UTankAimingComponent::AimAt(const FVector TargetLocation)
{
	ensure(Barrel != nullptr);
	/// Set up of arguments for SuggestProjectileVelocity().
	// Initializes OutLaunchVelocity to 0.
	FVector TossVelocity(0);
	const FVector StartLocation = Barrel->GetSocketLocation("ProjectileStart");
	const auto ActorsToIgnore = TArray<AActor*>();
	const auto bDrawDebug = false;

	// Calculates the suggested projectile velocity.
	const bool bHasProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		TossVelocity,
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
		// TODO: BUG! GetSafeNormal() seems to be unreliable in development build!
		// Stores normalized version of the suggested LaunchVelocity.
		//AimDirectionNormal = TossVelocity.GetSafeNormal();
		AimDirectionNormal = TossVelocity.GetClampedToMaxSize(1.0f);
		//UE_LOG(LogTemp, Warning, TEXT("AimDirectionNormal is normalized: %i"), AimDirectionNormal.IsNormalized());

		const auto ParentActorName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("[%s] Aiming from BarrelLocation: %s to TargetLocation: %s. SuggestedLaunchVelocity: %s"), *ParentActorName, *StartLocation.ToString(), *TargetLocation.ToString(), *AimDirectionNormal.ToString());

		RotateTurretAndBarrelTowards(AimDirectionNormal.Rotation());
	}
}

void UTankAimingComponent::Fire()
{
	if (AimState != EAimState::Reloading)
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

void UTankAimingComponent::RotateTurretAndBarrelTowards(FRotator TargetRotation) const
{
	if (!ensure(Barrel != nullptr))
	{
		return;
	}
	// Rotates the barrel (pitch).
	// Uses barrel for pitch rotation.
	const auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	const auto DeltaRotator = TargetRotation - BarrelRotator;

	// Translates AimDirectionNormal into pitch.
	Barrel->RotatePitch(DeltaRotator.Pitch);

	if (!ensure(Turret != nullptr))
	{
		return;
	}
	// TODO: The turret should always take the shortest direction relative to the crosshair.
	//UE_LOG(LogTemp, Warning, TEXT("Abs DeltaRotator.Yaw: %f"), FMath::Abs<float>(DeltaRotator.Yaw));
	/// Rotates the Turret (yaw), taking the shortest way.
	if (FMath::Abs<float>(DeltaRotator.Yaw) < 180.0f)
	{
		Turret->RotateYaw(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->RotateYaw(-DeltaRotator.Yaw);
	}
}
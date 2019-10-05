// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h" // Must be the last include.

#pragma region Enums

UENUM()
enum class EAimState : uint8
{
	Reloading,
	Aiming,
	Locked
};

#pragma endregion

#pragma region Forward Declarations

class UTankBarrel;
class UTankTurret;

#pragma endregion

/// Handles a tank's aiming.
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables

protected:

	// Defines the exclusive states aiming can be in.
	UPROPERTY(BlueprintReadOnly, Category = States)
		EAimState AimState = EAimState::Reloading;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firing)
		float LaunchSpeed = 4e3f;

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTimeSeconds = 3.0f;

	float LastFireTime = MIN_flt;

	FVector AimDirectionNormal = FVector::ZeroVector;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

#pragma endregion

#pragma region Functions

public:

	// Initializes the component's references.
	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitReferences(UTankBarrel* BarrelReference, UTankTurret* TurretReference);

	// Aims at a target location.
	void AimAt(const FVector TargetLocation);

	// Fires a projectile.
	UFUNCTION(BlueprintCallable, Category = Input)
		void Fire();

	EAimState GetAimState() const;

private:

	// Sets default values for this component's properties. Can be private in UE4!
	UTankAimingComponent();

	void RotateTurretAndBarrelTowards(FRotator TargetRotation) const;

	virtual void BeginPlay() override;

	bool IsBarrelMoving() const;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion
};

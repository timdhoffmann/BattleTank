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
	Locked,
	NoAmmo
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

	// BlueprintReadWrite can not be used on private members.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firing)
		float LaunchSpeed = 4e3f;

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		int32 StartingAmmo = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeSeconds = 3.0f;

	int32 Ammo = 0;

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

	// Fires a projectile.
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
		int32 GetRemainingAmmo() const;

	// Aims at a target location.
	void AimAt(const FVector TargetLocation);

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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

#pragma region Forward Declarations
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class UTankNavMovementComponent;
#pragma endregion

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
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		UTankNavMovementComponent* TankNavMovementComponent = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<class AProjectile> ProjectileBP;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ReloadTimeSeconds = 3.0f;
	float LastFireTime = 0.0f;
	// Barrel reference for spawning projectile.
	UTankBarrel* Barrel = nullptr;

#pragma endregion

#pragma region Functions

public:

	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet) const;
	// Aims at a target location.
	void AimAt(const FVector TargetLocation) const;
	UFUNCTION(BlueprintCallable, Category = Input)
		void Fire();

private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion
};

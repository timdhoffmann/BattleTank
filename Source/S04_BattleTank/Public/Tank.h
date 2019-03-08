// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

#pragma region Forward Declarations
class UTankAimingComponent;
#pragma endregion

UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

#pragma region Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Firing)
		float LaunchSpeed = 4e3f;
#pragma endregion

#pragma region Functions
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet) const;
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet) const;
	// Aims at a target location.
	void AimAt(const FVector TargetLocation) const;
#pragma endregion

protected:
	// The Component responsible for aiming.
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

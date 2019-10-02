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

/// Responsible for handling a tank's aiming.
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // Makes the component appear in the "add component" blueprint menu.
class S04_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables

protected:

	UPROPERTY(BlueprintReadOnly, Category = States)
		EAimState AimState = EAimState::Aiming;

private:

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

#pragma endregion

#pragma region Functions

public:

	// Initializes the component's references.
	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitReferences(UTankBarrel* BarrelReference, UTankTurret* TurretReference);

	// Aims at a target location.
	void AimAt(const FVector TargetLocation, const float LaunchSpeed) const;

	UTankBarrel* GetBarrel() const;

private:

	// Sets default values for this component's properties. Can be private in UE4!
	UTankAimingComponent();

	// Called after the owning Actor was created.
	virtual void InitializeComponent() override;

	void RotateTurretAndBarrelTowards(FVector Direction) const;

#pragma endregion
};

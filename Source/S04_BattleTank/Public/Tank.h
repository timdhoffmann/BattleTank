// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h" // Must be last include.

UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	/// Functions:

	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// Aims at a target location.
	void AimAt(const FVector TargetLocation) const;

protected:

	/// Variables:

	// The Actor Component responsible for aiming.
	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	/// Functions:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

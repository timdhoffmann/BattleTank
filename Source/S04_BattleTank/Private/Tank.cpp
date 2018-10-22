// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
	//Doesn't need to tick every frame.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers here, as they are added at construction.
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

#pragma region Overrides

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}
#pragma endregion

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) const
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector TargetLocation) const
{
	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
}
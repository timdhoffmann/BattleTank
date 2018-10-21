// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Misc/App.h"
#include "TankAimingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/// Functions:

	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// TODO: Add SetTurretReference().

	// Aims at a target location.
	void AimAt(const FVector TargetLocation, const float LaunchSpeed) const;

private:
	/// Variables:

	UStaticMeshComponent* Barrel = nullptr;

	/// Functions:
	void RotateBarrelTowards(FVector Direction) const;
};

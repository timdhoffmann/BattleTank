// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	/// Functions:

	// Sets default values for this pawn's properties
	ATank();

	// Aims at a target location.
	void AimAt(FVector TargetLocation) const;

private:

	/// Functions:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

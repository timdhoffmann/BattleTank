// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include!

/**
 * 
 */
UCLASS()
class S04_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	/// Variables.

	/// Functions.
	 void BeginPlay() override;
	 ATank* GetControlledTank() const;
};

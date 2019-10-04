// Copyright Tim Hoffmann (@timdhoffmann).

#include "Tank.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	//Doesn't need to tick every frame.
	PrimaryActorTick.bCanEverTick = false;
}

#pragma region Overrides

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion
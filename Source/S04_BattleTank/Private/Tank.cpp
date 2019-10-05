// Copyright Tim Hoffmann (@timdhoffmann).

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	//Doesn't need to tick every frame.
	PrimaryActorTick.bCanEverTick = false;
}
// Copyright Tim Hoffmann (@timdhoffmann).

#include "Tank.h"

// Sets default values
ATank::ATank()
{
	//Doesn't need to tick every frame.
	PrimaryActorTick.bCanEverTick = false;
}

#pragma region Overrides

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	const int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	const int32 ActualDamage = FMath::Clamp<int32>(DamagePoints, 0.0f, Health);

	Health -= ActualDamage;

	UE_LOG(LogTemp, Warning, TEXT("Damage applied: %i. Remaining Health: %i."), ActualDamage, Health);

	// If the damage depletes our health set our lifespan to zero - which will destroy the actor
	if (Health <= 0)
	{
		SetLifeSpan(0.001f);
	}

	return ActualDamage;
}

#pragma endregion
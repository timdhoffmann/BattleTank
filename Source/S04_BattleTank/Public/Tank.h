// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

// A Tank that can be controlled by a player or by the AI.
UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

#pragma region Functions

private:

	// Sets default values for this pawn's properties. Can be private in UE4!
	ATank();

	// Called by the engine when actor damage is dealt.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma endregion

#pragma region Variables

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int32 StartingHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Properties)
		int32 Health = StartingHealth;

#pragma endregion
};

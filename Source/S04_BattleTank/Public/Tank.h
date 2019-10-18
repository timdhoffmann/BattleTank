// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h" // Should be first include.
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Must be last include.

#pragma region Delegate & Event Signatures

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTank);

#pragma endregion

// A Tank that can be controlled by a player or by the AI.
UCLASS()
class S04_BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

#pragma region Functions

public:

	// Returns Health as a percentage of StartingHealth (read only).
	UFUNCTION(BlueprintPure, Category = Health)
		float GetHealthPercent() const;

private:

	// Sets default values for this pawn's properties. Can be private in UE4!
	ATank();

	// Called by the engine when actor damage is dealt.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

#pragma endregion

#pragma region Variables

public:
#pragma region Delegate & Event Instances

	// TODO: Check access level.
	FTank OnDied;

#pragma endregion

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int32 StartingHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = Properties)
		int32 Health = StartingHealth;

#pragma endregion
};

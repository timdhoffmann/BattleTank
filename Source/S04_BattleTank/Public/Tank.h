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

#pragma region Variables

public:

	// TODO: Remove once firing is moved to aiming component.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Firing)
		float LaunchSpeed = 4e3f;

#pragma endregion

#pragma region Functions

private:

	// Sets default values for this pawn's properties. Can be private in UE4!
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion
};

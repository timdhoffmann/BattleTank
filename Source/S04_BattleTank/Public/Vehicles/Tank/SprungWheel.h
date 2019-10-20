// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

#pragma region Forward Declarations

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

#pragma endregion

UCLASS()
class S04_BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

#pragma region Functions

public:
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Variables
	
private:

	/// Components.

	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* Mass = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* Spring = nullptr;

#pragma endregion

};

// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

#pragma region Forward Declarations

#pragma region Forward Declarations

class UPhysicsConstraintComponent;
class USphereComponent;

#pragma endregion

#pragma endregion

UCLASS()
class S04_BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

#pragma region Functions

public:
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Adds a force to the wheel to drive.
	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void InitConstraints() const;

	void ApplyForce() const;

	// Dynamic delegate. Must be a UFUNCTION!
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion

#pragma region Variables

private:

	float CurrentDrivingForceMagnitude = 0.f;

	/// Components.

	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* SpringPhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UPhysicsConstraintComponent* AxlePhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		USphereComponent* Wheel = nullptr;

#pragma endregion
};

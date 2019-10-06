// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

#pragma region Forward Declarations

class UParticleSystemComponent;

#pragma endregion
UCLASS()
class S04_BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

#pragma region Functions

public:
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(const float Speed) const;

#pragma endregion

#pragma region Variables

	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Category = Setup)
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Setup)
		UParticleSystemComponent* LaunchBlast = nullptr;

#pragma endregion
};

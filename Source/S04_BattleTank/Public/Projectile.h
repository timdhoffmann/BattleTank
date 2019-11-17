// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

#pragma region Forward Declarations

class UParticleSystemComponent;
class URadialForceComponent;

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

private:

	// Delegate to be called by the OnComponentHit physics event.
	// Must be a UFUNCTION.
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Called when the ProjectileTimer expires.
	void OnProjectileTimerExpired();

#pragma endregion

#pragma region Variables

	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		UParticleSystemComponent* ImpactExplosion = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
		URadialForceComponent* ImpactRadialForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float DestroyDelay = 8.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float Damage = 20.0f;

#pragma endregion
};

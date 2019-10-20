// Copyright Tim Hoffmann (@timdhoffmann).

#include "Common/SpawnPoint.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Vehicles/Tank/SprungWheel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(ActorToSpawn != nullptr))
	{
		// Using SpawnActorDeferred allows to attach the spawned actor first
		// and manually call its constructor and BeginPlay() afterwards by
		// invoking UGameplayStatics::FinishSpawningActor().
		const auto SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(
			ActorToSpawn,
			GetComponentTransform(),
			GetOwner(),
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

		UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	}
}

// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
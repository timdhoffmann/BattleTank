// Copyright Tim Hoffmann (@timdhoffmann).

#include "Common/SpawnPoint.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Vehicles/Tank/SprungWheel.h"

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
		auto Actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);

		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
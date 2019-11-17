// Copyright Tim Hoffmann (@timdhoffmann).

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

#pragma region Forward Declarations

class AActor;

#pragma endregion

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class S04_BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

#pragma region Functions

public:
	// Sets default values for this component's properties
	USpawnPoint();

	AActor* GetSpawnedActor() const { return SpawnedActor; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Variables

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AActor> ActorToSpawn = nullptr;

	// A reference to the actor when it has been spawned.
	AActor* SpawnedActor = nullptr;

#pragma endregion
};

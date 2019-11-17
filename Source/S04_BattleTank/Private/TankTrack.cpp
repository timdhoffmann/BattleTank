// Copyright Tim Hoffmann (@timdhoffmann).

#include "TankTrack.h"
#include "Components/StaticMeshComponent.h"
#include "Vehicles/Tank/SprungWheel.h"
#include "Common/SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma region Overrides

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

void UTankTrack::DriveTrack(float CurrentThrottle) const
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] DriveTrack called"), *GetName());
	
	const float Force = MaxDrivingForce * CurrentThrottle;

	const TArray<ASprungWheel*> Wheels = GetWheels();
	const float ForcePerWheel = Force / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] adding force %f to wheel %s"), *GetName(), Force, *Wheel->GetName());
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

void UTankTrack::SetThrottle(const float Throttle) const
{
	const float ClampedThrottle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
	DriveTrack(ClampedThrottle);
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> OUT Wheels;

	TArray<USceneComponent*> OUT ChildComponents;
	GetChildrenComponents(true, ChildComponents);
	for (auto& Child : ChildComponents)
	{
		// Checks that Child is a USpawnPoint.
		if (!(Child->GetClass() == USpawnPoint::StaticClass())) continue;

		AActor* SpawnedActor = Cast<USpawnPoint>(Child)->GetSpawnedActor();

		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnedActor);
		if (SprungWheel == nullptr) continue;
		Wheels.Add(SprungWheel);
	}
	return Wheels;
}
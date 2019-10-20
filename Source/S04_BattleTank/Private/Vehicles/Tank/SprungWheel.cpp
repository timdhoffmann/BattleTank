// Copyright Tim Hoffmann (@timdhoffmann).

//#include "SprungWheel.h"
#include "Vehicles/Tank/SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>("Mass");
	SetRootComponent(Mass);

	Wheel = CreateDefaultSubobject < UStaticMeshComponent>("Wheel");
	// Preferred way of attaching to another component (constructor-only).
	Wheel->SetupAttachment(RootComponent);

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>("Spring");
	Spring->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
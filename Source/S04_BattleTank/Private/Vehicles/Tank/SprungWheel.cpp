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

	// The Spring should be the root component to make the SprungWheel not pop out of the hierarchy.
	// The other components have simulate physics enabled, which causes this problem.
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>("Spring");
	SetRootComponent(Spring);

	Wheel = CreateDefaultSubobject <UStaticMeshComponent>("Wheel");
	// Preferred way of attaching to another component (constructor-only).
	Wheel->SetupAttachment(Spring);
}

#pragma region Overrides

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	InitConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma endregion

void ASprungWheel::InitConstraints() const
{
	const AActor* ParentActor = GetAttachParentActor();
	if (!ensure(ParentActor != nullptr)) return;

	UPrimitiveComponent* ParentRootComponent = Cast<UPrimitiveComponent>(ParentActor->GetRootComponent());
	if (!ensure(ParentRootComponent != nullptr)) return;

	Spring->SetConstrainedComponents(
		ParentRootComponent,
		NAME_None,
		Wheel,
		NAME_None
	);
}
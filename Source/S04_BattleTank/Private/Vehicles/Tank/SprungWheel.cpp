// Copyright Tim Hoffmann (@timdhoffmann).

//#include "SprungWheel.h"
#include "Vehicles/Tank/SprungWheel.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Sets the actor to tick post physics, so we can react to collision in tick.
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	// The SpringPhysicsConstraint should be the root component to make the SprungWheel not pop out of the hierarchy.
	// The other components have simulate physics enabled, which causes this problem.
	SpringPhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("SpringPhysicsConstraint");
	SetRootComponent(SpringPhysicsConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>("Axle");
	// Preferred way of attaching to another component (constructor-only).
	Axle->SetupAttachment(SpringPhysicsConstraint);
	Axle->SetSimulatePhysics(true);

	AxlePhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("AxlePhysicsConstraint");
	AxlePhysicsConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>("Wheel");
	Wheel->SetupAttachment(Axle);
	Wheel->SetSimulatePhysics(true);
}

#pragma region Overrides

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	// Makes sure that the wheel generates Hit events.
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	InitConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ensures post physics execution.
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		// Resets the DrivingForce before the next frame.
		CurrentDrivingForceMagnitude = 0.f;
	}
}

#pragma endregion

void ASprungWheel::InitConstraints() const
{
	// Initializes SpringPhysicConstraint.

	const AActor* ParentActor = GetAttachParentActor();
	if (!ensure(ParentActor != nullptr)) return;

	UPrimitiveComponent* ParentRootComponent = Cast<UPrimitiveComponent>(ParentActor->GetRootComponent());
	if (!ensure(ParentRootComponent != nullptr)) return;

	SpringPhysicsConstraint->SetConstrainedComponents(
		ParentRootComponent,
		NAME_None,
		Axle,
		NAME_None
	);

	// Initializes AxlePhysicsConstraint.

	AxlePhysicsConstraint->SetConstrainedComponents(
		Axle,
		NAME_None,
		Wheel,
		NAME_None
	);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentDrivingForceMagnitude += ForceMagnitude;
}

void ASprungWheel::ApplyForce() const
{
	const FVector DrivingForce = Axle->GetForwardVector() * CurrentDrivingForceMagnitude;
	Wheel->AddForce(DrivingForce);
}

// Applies DrivingForce to wheel only on physics collision.
void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: Called multiple times within the same frame. Does that cause issues?

	if (!Hit.IsValidBlockingHit()) return;
	UE_LOG(LogTemp, Warning, TEXT("[%s] OnHit triggered with: %s"), *GetName(), *OtherComponent->GetName());

	ApplyForce();
}
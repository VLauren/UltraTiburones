#include "Swimer.h"


// CONSTRUCTOR
ASwimer::ASwimer()
{
	PrimaryActorTick.bCanEverTick = true;

	// colision
	// brazo de cam
	// cam
	// movimiento

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(100, 100, 100));
	RootComponent = CollisionBox;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 700.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	CollisionBox->SetVisibility(true);
	CollisionBox->SetHiddenInGame(false);
}


void ASwimer::BeginPlay()
{
	Super::BeginPlay();
	
	// pillo mesh
}

//====================================================================
// TICK
//====================================================================

void ASwimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwimer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


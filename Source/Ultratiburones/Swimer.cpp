#include "Swimer.h"

const float ASwimer::MOVEMENT_SPEED = 500.0f;

// CONSTRUCTOR
ASwimer::ASwimer()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(100, 100, 100));
	CollisionBox->SetCollisionProfileName("Felipe");
	CollisionBox->CanCharacterStepUpOn = ECB_No;
	CollisionBox->bShouldUpdatePhysicsVolume = true;
	CollisionBox->bCheckAsyncSceneOnMove = false;
	CollisionBox->SetCanEverAffectNavigation(false);
	CollisionBox->bDynamicObstacle = true;
	RootComponent = CollisionBox;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 700.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CollisionBox);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
	}

	ProvisionalMesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("ProvisionalMesh"));
	if (ProvisionalMesh)
	{
		ProvisionalMesh->AlwaysLoadOnClient = true;
		ProvisionalMesh->AlwaysLoadOnServer = true;
		ProvisionalMesh->bOwnerNoSee = false;
		ProvisionalMesh->bCastDynamicShadow = true;
		ProvisionalMesh->bAffectDynamicIndirectLighting = true;
		ProvisionalMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		ProvisionalMesh->SetupAttachment(CollisionBox);
		ProvisionalMesh->bGenerateOverlapEvents = false;
		ProvisionalMesh->SetCanEverAffectNavigation(false);
	}

	// Componente de movimiento
	Movement = CreateDefaultSubobject<USwimerMovement>(TEXT("Movimiento"));
	Movement->UpdatedComponent = RootComponent;


	CollisionBox->SetVisibility(true);
	CollisionBox->SetHiddenInGame(false);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
} 

void ASwimer::BeginPlay()
{
	Super::BeginPlay();

	Movement->UpdatedComponent = RootComponent;
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

	// input de camara
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// input de movimiento (controller)
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwimer::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASwimer::MoveForward);
}




void ASwimer::MoveForward(float AxisValue)
{
	if (Movement)
	{
		UE_LOG(LogTemp, Warning, TEXT("Forwqrd %f"), AxisValue);
		if (Movement->UpdatedComponent == RootComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("Foasdfasdfasdfasdfrwqrd %f"), AxisValue);
		}
	}

	if (Movement && (Movement->UpdatedComponent == RootComponent))
	{
		Movement->AddInputVector(GetControlRotation().RotateVector(GetActorForwardVector()) * AxisValue);
	}
}

void ASwimer::MoveRight(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent))
		// Movement->AddInputVector(FRotator(0, GetControlRotation().Yaw, 0).RotateVector(GetActorRightVector()) * AxisValue);
		Movement->AddInputVector(GetControlRotation().RotateVector(GetActorRightVector()) * AxisValue);
}


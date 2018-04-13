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
	CollisionBox->bShouldUpdatePhysicsVolume = true;
	CollisionBox->bCheckAsyncSceneOnMove = false;
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


	CollisionBox->SetVisibility(true);
	CollisionBox->SetHiddenInGame(false);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


void ASwimer::BeginPlay()
{
	Super::BeginPlay();
	
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

}


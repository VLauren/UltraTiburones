#include "Swimer.h"
#include "Item.h"
#include "Engine/Engine.h"

const float ASwimer::MOVEMENT_SPEED = 500.0f;
ASwimer* ASwimer::Instance;

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
	CameraArm->TargetArmLength = 800.0f;
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

	// visibilidad de colider
	CollisionBox->SetVisibility(false);
	CollisionBox->SetHiddenInGame(true);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
} 

void ASwimer::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;

	Movement->UpdatedComponent = RootComponent;

	AnimState = ESwimerAnimState::AS_IDLE;
	if(Mesh != nullptr)
		Mesh->PlayAnimation(AnimIdle, true);

	// MusicBase->VolumeMultiplier = 0;
	// MusicAdditional->VolumeMultiplier = 1;
	// UGameplayStatics::PlaySound2D(GetWorld(), MusicBase);
	// UGameplayStatics::PlaySound2D(GetWorld(), MusicAdditional);


}

//====================================================================
// TICK
//====================================================================

void ASwimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		FString msg = FString::Printf(TEXT("%d/%d"),AItem::CollectedItems, AItem::ItemsToCollect);
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Green, msg);
	}
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
	PlayerInputComponent->BindAxis("MoveUp", this, &ASwimer::MoveUp);
}



void ASwimer::MoveForward(float AxisValue)
{
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

void ASwimer::MoveUp(float AxisValue)
{
	if (Movement && (Movement->UpdatedComponent == RootComponent))
		Movement->AddInputVector(GetControlRotation().RotateVector(GetActorUpVector()) * AxisValue);
}

void ASwimer::Animate(ESwimerAnimState Anim)
{
	if (AnimState == Anim)
		return;

	AnimState = Anim;
	if (Anim == ESwimerAnimState::AS_IDLE && Mesh != nullptr)
		Mesh->PlayAnimation(AnimIdle, true);
	if (Anim == ESwimerAnimState::AS_SWIM && Mesh != nullptr)
		Mesh->PlayAnimation(AnimSwim, true);
}

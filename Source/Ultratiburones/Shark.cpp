// Fill out your copyright notice in the Description page of Project Settings.

#include "Shark.h"
#include "Swimer.h"

const float AShark::MOVEMENT_SPEED = 300.0f;

const float SIGHT_ANGLE = 45;
const float SIGHT_DISTANCE = 1500;
const float STOP_CHASE_DISTANCE = 2000;


// Sets default values
AShark::AShark()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(100, 100, 100));
	CollisionBox->SetCollisionProfileName("Paco");
	CollisionBox->CanCharacterStepUpOn = ECB_No;
	CollisionBox->bShouldUpdatePhysicsVolume = true;
	CollisionBox->bCheckAsyncSceneOnMove = false;
	CollisionBox->SetCanEverAffectNavigation(false);
	CollisionBox->bDynamicObstacle = true;
	RootComponent = CollisionBox;

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
	Movement = CreateDefaultSubobject<USharkMovement>(TEXT("Movimiento"));
	Movement->UpdatedComponent = RootComponent;



}

// Called when the game starts or when spawned
void AShark::BeginPlay()
{
	Super::BeginPlay();
	
	PatrolA = GetActorLocation();
	if (Waypoint != nullptr)
		PatrolB = Waypoint->GetActorLocation();
	else
		PatrolB = GetActorLocation() + FVector(500, 0, 0);

	SharkState = ESharkState::ES_PATROL_B;
}

// Called every frame
void AShark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SharkState == ESharkState::ES_CHASE)
	{
		if (FVector::Dist(GetActorLocation(), ASwimer::Instance->GetActorLocation()) < STOP_CHASE_DISTANCE)
			SharkState = ESharkState::ES_PATROL_A;
	}
	if (SharkState == ESharkState::ES_PATROL_A)
	{
		if (FVector::Dist(GetActorLocation(), PatrolA) <= 100)
			SharkState = ESharkState::ES_PATROL_B;
	}
	if (SharkState == ESharkState::ES_PATROL_B)
	{
		if(FVector::Dist(GetActorLocation(), PatrolB) <= 100)
			SharkState = ESharkState::ES_PATROL_A;
	}

	if (SharkState == ESharkState::ES_PATROL_B || SharkState == ESharkState::ES_PATROL_A)
	{
		if (CheckSight())
			SharkState = ESharkState::ES_CHASE;
	}

	UE_LOG(LogTemp, Warning, TEXT("STATE: %s"), SharkState == ESharkState::ES_CHASE ? TEXT("CHASE") : TEXT("PATROL"));
}

// Called to bind functionality to input
void AShark::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AShark::CheckSight()
{
	float distance = FVector::Dist(GetActorLocation(), ASwimer::Instance->GetActorLocation());

	// FVector DirA = RootComponent->GetComponentRotation().Vector().GetSafeNormal();
	FVector DirA = Movement->direccion;

	FVector DirB = (ASwimer::Instance->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(DirA,DirB)));

	// UE_LOG(LogTemp, Warning, TEXT("ANGLE: %f, DISTANCE: %f"), angle, distance);

	return distance <= SIGHT_DISTANCE && angle <= SIGHT_ANGLE;
}


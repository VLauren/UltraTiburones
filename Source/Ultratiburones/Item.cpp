// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Swimer.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

int AItem::CollectedItems = 0;
int AItem::ItemsToCollect = 0;

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->InitBoxExtent(FVector(50, 50, 50));

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(BoxCollision);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// visibilidad de colider
	// BoxCollision->SetVisibility(true);
	// BoxCollision->SetHiddenInGame(false);

	BoxCollision->bGenerateOverlapEvents = true;

	// evento de overlap del hitbox
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlap);
	ItemsToCollect++;

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherComp != nullptr)
	{
		// Si es enemigo, le hago daño
		if (OtherComp->GetOwner()->GetClass()->IsChildOf<ASwimer>())
			CollectedItems++;

		// Ganar
		if (CollectedItems >= ItemsToCollect)
		{
			CollectedItems = 0;
			UGameplayStatics::OpenLevel(this, TEXT("/Game/Level/WinScreen"));
		}
		else
			Destroy();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "SharkMovement.h"
#include "Shark.h"


void USharkMovement::BeginPlay()
{
	Super::BeginPlay();

	ProvisionalMesh = ((AShark*)GetOwner())->ProvisionalMesh;
	Mesh = ((AShark*)GetOwner())->Mesh;

	StartMeshRotation = ProvisionalMesh->RelativeRotation;
}

void USharkMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
		return;

	AShark* Shark;
	Shark = (AShark*)GetOwner();

	if (true)
	{
		// Movimiento

		//HACK
		// Shark->SharkState = ESharkState::ES_PATROL_B;

		if (Shark->SharkState == ESharkState::ES_CHASE)
		{
			direccion = (ASwimer::Instance->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		}
		if (Shark->SharkState == ESharkState::ES_PATROL_A)
		{
			direccion = (Shark->PatrolA - GetActorLocation()).GetSafeNormal();
		}
		if (Shark->SharkState == ESharkState::ES_PATROL_B)
		{
			direccion = (Shark->PatrolB - GetActorLocation()).GetSafeNormal();
		}

		FVector movimientoEsteFrame = direccion * DeltaTime * AShark::MOVEMENT_SPEED;

		if (!movimientoEsteFrame.IsNearlyZero())
		{
			FHitResult Hit;

			// Movimiento
			SafeMoveUpdatedComponent(movimientoEsteFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

			// Si chocamos con algo, me deslizo sobre el
			if (Hit.IsValidBlockingHit())
				SlideAlongSurface(movimientoEsteFrame, 1.f - Hit.Time, Hit.Normal, Hit);

			// Rotacion de la malla
			FRotator TargetRotation = movimientoEsteFrame.Rotation() + StartMeshRotation;
			CurrentRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.1f);

			if(ProvisionalMesh != nullptr)
				ProvisionalMesh->SetRelativeRotation(CurrentRotation);
			if(Mesh != nullptr)
				Mesh->SetRelativeRotation(CurrentRotation);
		}
	}
}

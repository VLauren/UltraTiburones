
#include "SwimerMovement.h"
#include "Swimer.h"

void USwimerMovement::BeginPlay()
{
	Super::BeginPlay();

	ProvisionalMesh = ((ASwimer*)GetOwner())->ProvisionalMesh;
	Mesh = ((ASwimer*)GetOwner())->Mesh;
	// Arrow = ((ASwimer*)GetOwner())->Arrow;

	if(ProvisionalMesh != nullptr)
		StartMeshRotation = ProvisionalMesh->RelativeRotation;
	// if(Arrow != nullptr)
		// StartMeshRotation = Arrow->RelativeRotation;
	if(Mesh != nullptr)
		StartMeshRotation = Mesh->RelativeRotation;
}

void USwimerMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
		return;

	// Calculo el vector de movimiento
	FVector movimientoEsteFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * ASwimer::MOVEMENT_SPEED;
	
	if (!movimientoEsteFrame.IsNearlyZero())
	{
		FHitResult Hit;

		// FRotator forward = ((ASwimer*)GetOwner())->CameraArm->RelativeRotation;
		// movimientoEsteFrame = forward.RotateVector(movimientoEsteFrame);

		// Movimiento
		SafeMoveUpdatedComponent(movimientoEsteFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Si chocamos con algo, me deslizo sobre el
		if (Hit.IsValidBlockingHit())
			SlideAlongSurface(movimientoEsteFrame, 1.f - Hit.Time, Hit.Normal, Hit);

		// Rotacion de la malla
		FRotator ctrlRot = movimientoEsteFrame.Rotation();

		FRotator TargetRotation = FRotator(ctrlRot.Roll, ctrlRot.Yaw, -ctrlRot.Pitch) + StartMeshRotation;
		// FRotator TargetRotation = ctrlRot + StartMeshRotation;

		CurrentRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.05f);

		if(ProvisionalMesh != nullptr)
			ProvisionalMesh->SetRelativeRotation(CurrentRotation);
		// if(Arrow != nullptr)
			// Arrow->SetRelativeRotation(CurrentRotation);
		if(Mesh != nullptr)
			Mesh->SetRelativeRotation(CurrentRotation);

		((ASwimer*)GetOwner())->Animate(ESwimerAnimState::AS_SWIM);
	}
	else
	{
		((ASwimer*)GetOwner())->Animate(ESwimerAnimState::AS_IDLE);

		// Rotacion de la malla
		// FRotator ctrlRot = movimientoEsteFrame.Rotation();

		// FRotator TargetRotation = FRotator(ctrlRot.Roll, ctrlRot.Yaw, -ctrlRot.Pitch) + StartMeshRotation;
		FRotator TargetRotation = FRotator(0, CurrentRotation.Yaw, 0);
		CurrentRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.005f);

		if(ProvisionalMesh != nullptr)
			ProvisionalMesh->SetRelativeRotation(CurrentRotation);
		// if(Arrow != nullptr)
			// Arrow->SetRelativeRotation(CurrentRotation);
		if(Mesh != nullptr)
			Mesh->SetRelativeRotation(CurrentRotation);
	}
}



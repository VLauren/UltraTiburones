
#include "SwimerMovement.h"
#include "Swimer.h"

void USwimerMovement::BeginPlay()
{
	Super::BeginPlay();

	ProvisionalMesh = ((ASwimer*)GetOwner())->ProvisionalMesh;

	StartMeshRotation = ProvisionalMesh->RelativeRotation;
}

void USwimerMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
		return;

	// Calculo el vector de movimiento
	FVector movimientoEsteFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 502;
	UE_LOG(LogTemp, Warning, TEXT("SwimTick %f"), movimientoEsteFrame.X);
	
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
		CurrentRotation = FMath::Lerp(CurrentRotation, TargetRotation, 0.05f);
		ProvisionalMesh->SetRelativeRotation(CurrentRotation);

		// TODO Estado de animacion -> nadar
	}
}



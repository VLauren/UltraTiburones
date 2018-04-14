#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SwimerMovement.h"
#include "GameFramework/Pawn.h"
#include "Swimer.generated.h"

UENUM()
enum class ESwimerAnimState : uint8
{
	AS_IDLE		UMETA(DisplayName = "Idle"),
	AS_SWIM		UMETA(DisplayName = "Swim")
};

UCLASS()
class ULTRATIBURONES_API ASwimer : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;

public:	

	ASwimer();


	// ==========================================
	// Propiedades

	static const float MOVEMENT_SPEED;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* ProvisionalMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		class USwimerMovement* Movement;

	static ASwimer* Instance;

	// ==========================================
	// Metodos

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Metodos de input
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue); 
	void MoveUp(float AxisValue); 
	
	//Animaciones
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimationAsset* AnimIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimationAsset* AnimSwim;

	ESwimerAnimState AnimState;

	void Animate(ESwimerAnimState Anim);
};




























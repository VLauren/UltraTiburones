#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
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
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

protected:
	virtual void BeginPlay() override;

public:	

	ASwimer();


	// ==========================================
	// Propiedades

	float MovementSpeed = 500;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		class USwimerMovement* Movement;

	// ==========================================
	// Metodos

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};




























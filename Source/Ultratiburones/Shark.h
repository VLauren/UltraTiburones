// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "SharkMovement.h"
#include "GameFramework/Pawn.h"
#include "Shark.generated.h"

UENUM()
enum class ESharkState : uint8
{
	ES_PATROL_A,
	ES_PATROL_B,
	ES_CHASE,
	ES_RETURN
};

UCLASS()
class ULTRATIBURONES_API AShark : public APawn
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

protected:

	virtual void BeginPlay() override;

public:	

	AShark();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		AActor* Waypoint;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* ProvisionalMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		class USharkMovement* Movement;

	static const float MOVEMENT_SPEED;

	FVector PatrolA, PatrolB;

	UPROPERTY(EditAnywhere)
		ESharkState SharkState;
};

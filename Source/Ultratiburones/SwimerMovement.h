// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SwimerMovement.generated.h"

/**
 * 
 */
UCLASS()
class ULTRATIBURONES_API USwimerMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	class USkeletalMeshComponent* Mesh = nullptr;
	class UStaticMeshComponent* ProvisionalMesh = nullptr;
	// class UArrowComponent* Arrow = nullptr;

	FRotator StartMeshRotation;
	FRotator CurrentRotation;
	
	FVector Move;
	
};

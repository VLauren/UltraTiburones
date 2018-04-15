// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Swimer.h"
#include "SharkMovement.generated.h"

/**
 * 
 */
UCLASS()
class ULTRATIBURONES_API USharkMovement : public UPawnMovementComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	FVector direccion;

private:
	class USkeletalMeshComponent* Mesh = nullptr;

	FRotator StartMeshRotation;
	FRotator CurrentRotation;

};

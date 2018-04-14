// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "SharkVolumeChange.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTRATIBURONES_API USharkVolumeChange : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USharkVolumeChange();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static USharkVolumeChange* Instance;

	UAudioComponent* AudioComponent;
		
	void SetVolume(float volume);
	
};

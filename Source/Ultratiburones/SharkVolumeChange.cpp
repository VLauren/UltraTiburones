
#include "SharkVolumeChange.h"

USharkVolumeChange* USharkVolumeChange::Instance;

USharkVolumeChange::USharkVolumeChange()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USharkVolumeChange::BeginPlay()
{
	Super::BeginPlay();

	// AudioComponent = GetOwner()->GetComponentByClass<UAudioComponent>();
	// AudioComponent = GetOwner()->GetComponents<UAudioComponent*>()[0];

	TArray<UAudioComponent*> AudioComps;
	GetOwner()->GetComponents<UAudioComponent>(AudioComps);
	AudioComponent = AudioComps[0];

	Instance = this;
}

void USharkVolumeChange::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USharkVolumeChange::SetVolume(float volume)
{
	AudioComponent->VolumeMultiplier = volume;
}


#include "FixedCameraComponent.h"

UFixedCameraComponent::UFixedCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UFixedCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	AFixedCameraManager::AddCamera(GetOwner());


	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta,playerRef->GetPathName());
	}



	AFixedCameraManager::ChangeCamera();

}

void UFixedCameraComponent::BeginDestroy()
{
	Super::BeginDestroy();
}



// Called every frame
void UFixedCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
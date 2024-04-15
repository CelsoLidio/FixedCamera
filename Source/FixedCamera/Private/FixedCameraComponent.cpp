// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedCameraComponent.h"

// Sets default values for this component's properties
UFixedCameraComponent::UFixedCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UFixedCameraManager::GetInstance()->AddCamera(GetOwner());

}


// Called when the game starts
void UFixedCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	

	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta,playerRef->GetPathName());
	}
	

	
	UFixedCameraManager::GetInstance()->ChangeCamera();
}


// Called every frame
void UFixedCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


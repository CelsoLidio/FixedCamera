#include "FixedCameraComponent.h"

UFixedCameraComponent::UFixedCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UFixedCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ComponentTags.Add("FixedCameraComponent");

	AFixedCameraManager::AddCamera(GetOwner());



	if (GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		playerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta,playerRef->GetPathName());
	}



	AFixedCameraManager::ChangeCamera();

}


void UFixedCameraComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	if (GetWorld())
	{
		AFixedCameraManager::ChangeCamera();
	}
}




// Called every frame
void UFixedCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	

	AFixedCameraManager::ChangeCamera();
	/*
	FHitResult hitResult;

	FVector startPos = GetOwner()->GetActorLocation();

	FVector endPos = startPos + GetOwner()->GetActorForwardVector() * 50000;

	FCollisionQueryParams paramsCollision;
	paramsCollision.AddIgnoredActor(GetOwner());


	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECollisionChannel::ECC_Pawn,paramsCollision))
	{
		printf("%s", *hitResult.GetActor()->GetActorNameOrLabel());
	}

	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, true, 2.0f, 0.0f, 5.0f);
	*/
}
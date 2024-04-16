// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedCameraManager.h"


AFixedCameraManager::AFixedCameraManager()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = sceneRoot;

}



void AFixedCameraManager::BeginPlay()
{
	Super::BeginPlay();

}


void AFixedCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AFixedCameraManager::ChangeCamera()
{
	if (!IsValid(GEngine->GameViewport))
	{
		return;
	}

	UWorld* world = GEngine->GameViewport->GetWorld();

	

	auto auxManagerCam = NewObject<AFixedCameraManager>();


	AFixedCameraManager* managerCam = GetCameraManager();

	auto* playerPawn = UGameplayStatics::GetPlayerPawn(world, 0);


	if (managerCam->allCameras.IsEmpty())
	{
		return;
	}

	AActor* closerCam = nullptr;

	float minorDistCam = FVector::Distance(playerPawn->GetActorLocation(), managerCam->allCameras[0]->GetActorLocation());

	
	for(auto currCamera : managerCam->allCameras)
	{
		if (!IsValid(currCamera))
		{
			managerCam->allCameras.Remove(currCamera);
			continue;
		}

		auxManagerCam->SetTickComponentByTag(currCamera, "FixedCameraComponent", false);
		

		float distCams = FVector::Distance(playerPawn->GetActorLocation(), currCamera->GetActorLocation());

		printf("Distancia = %f", distCams);
		
		if (distCams <= minorDistCam)
		{
			closerCam = currCamera;
		}
		
	}

	if (IsValid(closerCam))
	{
		auxManagerCam->SetTickComponentByTag(closerCam, "FixedCameraComponent", true);
		UGameplayStatics::GetPlayerController(world, 0)->SetViewTarget(closerCam);
	}
	else
	{
		print("Closer Camera not found");
	}
	
}




void AFixedCameraManager::AddCamera(AActor* newCamera)
{

	AFixedCameraManager* auxManager = NewObject<AFixedCameraManager>();

	AFixedCameraManager* managerCam = GetCameraManager();

	if (!IsValid(managerCam))
	{
		print("Manager Camera is NULL");
		return;
	}

	//printf("%s", *managerCam->GetActorNameOrLabel());

	managerCam->allCameras.Add(newCamera);

}


AFixedCameraManager* AFixedCameraManager::GetCameraManager()
{
	UWorld* world = GEngine->GameViewport->GetWorld();


	AFixedCameraManager* managerRef;
	TArray<AActor*> foundActors;

	UGameplayStatics::GetAllActorsOfClass(world, AFixedCameraManager::StaticClass(), foundActors);

	if (foundActors.Num() <= 0)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride;
		managerRef = world->SpawnActor<AFixedCameraManager>(AFixedCameraManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
	else
	{
		managerRef = Cast<AFixedCameraManager>(foundActors[0]);
	}

	return managerRef;
}



void AFixedCameraManager::SetTickComponentByTag(AActor* actorRef, FName tagComponent, bool isEnabled)
{
	auto* compActor = actorRef->FindComponentByTag<UActorComponent>(tagComponent);

	if (IsValid(compActor))
	{
		compActor->SetComponentTickEnabled(isEnabled);
	}
}

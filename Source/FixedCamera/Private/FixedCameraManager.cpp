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
	UWorld* world = GEngine->GameViewport->GetWorld();

	AFixedCameraManager* managerCam = GetCameraManager();

	auto* playerPawn = UGameplayStatics::GetPlayerPawn(world, 0);


	if (managerCam->allCameras.IsEmpty())
	{
		return;
	}

	AActor* closerCam = nullptr;

	float minorDistCam = FVector::Distance(playerPawn->GetActorLocation(), managerCam->allCameras[0]->GetActorLocation());

	
	for(int eachCamera = 0; eachCamera< managerCam->allCameras.Num(); eachCamera++)
	{
		AActor* currCamera = Cast<AActor>(managerCam->allCameras[eachCamera]);
		
		float distCams = FVector::Distance(playerPawn->GetActorLocation(), currCamera->GetActorLocation());


		if (distCams <= minorDistCam)
		{
			closerCam = currCamera;
		}
		
	}

	if (IsValid(closerCam))
	{
		UGameplayStatics::GetPlayerController(world, 0)->SetViewTarget(closerCam);
		printf("camera name = %s", *closerCam->GetActorNameOrLabel());
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


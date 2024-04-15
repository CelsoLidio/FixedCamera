// Fill out your copyright notice in the Description page of Project Settings.


#include "FixedCameraManager.h"

UFixedCameraManager* UFixedCameraManager::instanceManager = nullptr;

UFixedCameraManager::UFixedCameraManager()
{
	instanceManager = this;
}


UFixedCameraManager* UFixedCameraManager::GetInstance()
{
	if (!instanceManager)
	{
		instanceManager = NewObject<UFixedCameraManager>();
		instanceManager->AddToRoot();
	}

	return instanceManager;
}

void UFixedCameraManager::ChangeCamera()
{

	for(int eachCamera = 0; eachCamera< allCameras.Num(); eachCamera++)
	{
		AActor* currCamera = allCameras[eachCamera];
		

		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString(*currCamera->GetActorNameOrLabel()));
	}


}

void UFixedCameraManager::AddCamera(AActor* newCamera)
{
	allCameras.Add(newCamera);

}



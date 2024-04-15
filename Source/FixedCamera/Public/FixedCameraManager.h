// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FixedCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class FIXEDCAMERA_API UFixedCameraManager : public UObject
{
	GENERATED_BODY()
	
public:
	

	static UFixedCameraManager* GetInstance();

	

	void ChangeCamera();

	void AddCamera(AActor* newCamera);

private:
	
	UFixedCameraManager();

	static UFixedCameraManager* instanceManager;

	TArray<AActor*> allCameras;

	
};

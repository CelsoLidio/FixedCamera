// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../PrintStrings.h"
#include "FixedCameraManager.generated.h"


/**
 * 
 */
UCLASS()
class FIXEDCAMERA_API AFixedCameraManager : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFixedCameraManager();
	


protected:
	virtual void BeginPlay() override;


public:
	
	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
	TArray<AActor*> allCameras;


	static void AddCamera(AActor* newCamera);

	static void ChangeCamera();

private:

	//static AFixedCameraManager* instanceManager;

	AFixedCameraManager* managerCamActor;

	USceneComponent* sceneRoot;

	static AFixedCameraManager* GetCameraManager();

	void SetTickComponentByTag(AActor* actorRef, FName tagComponent, bool isEnabled);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"


#include "FixedCameraPlayer.generated.h"


class UInputMappingContext;
class UInputAction;


UCLASS()
class AFixedCameraPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFixedCameraPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MovePlayer(const FInputActionValue& value);

	void RegisterDirPlayer(const FInputActionValue& value);

private:

	UPROPERTY(EditAnywhere, Category = InputPlayer)
	UInputMappingContext* mapInputPlayer;

	UPROPERTY(EditAnywhere, Category = InputPlayer)
	UInputAction* movementAction;

	FRotator playerRotMove;
	FVector2D movementVector;

};

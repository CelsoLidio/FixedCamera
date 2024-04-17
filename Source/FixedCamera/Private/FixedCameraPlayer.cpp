// Fill out your copyright notice in the Description page of Project Settings.
#include "FixedCameraPlayer.h"

// Sets default values
AFixedCameraPlayer::AFixedCameraPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void AFixedCameraPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subSystem->AddMappingContext(mapInputPlayer, 0);
		}
	}
	
	playerRotMove = Controller->GetViewTarget()->GetActorRotation();
	movementVector = FVector2D::ZeroVector;
}

// Called every frame
void AFixedCameraPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AFixedCameraPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(movementAction, ETriggerEvent::Triggered, this, &AFixedCameraPlayer::MovePlayer);

		enhancedInputComponent->BindAction(movementAction, ETriggerEvent::Started, this, &AFixedCameraPlayer::RegisterDirPlayer);
		enhancedInputComponent->BindAction(movementAction, ETriggerEvent::Completed, this, &AFixedCameraPlayer::RegisterDirPlayer);

	}
}

void AFixedCameraPlayer::MovePlayer(const FInputActionValue& value)
{

	//const FVector2D movementVector = value.Get<FVector2D>();

	
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Emerald, "Input movimento = " + movementVector.ToString());
	
	if (movementVector != value.Get<FVector2D>())
	{
		movementVector = value.Get<FVector2D>();
		playerRotMove = Controller->GetViewTarget()->GetActorRotation();
	}

	


	const FRotator rotationPlayer = playerRotMove;
	const FRotator YawRotation(0.f, rotationPlayer.Yaw, 0.f);

	const FVector forwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(forwardDir, movementVector.Y);

	const FVector rightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(rightDir, movementVector.X);



	/*const FVector forwardDir = GetActorForwardVector();
	AddMovementInput(forwardDir, movementVector.Y);

	const FVector rightDir = GetActorRightVector();
	AddMovementInput(rightDir, movementVector.X);*/



}

void AFixedCameraPlayer::RegisterDirPlayer(const FInputActionValue& value)
{
	playerRotMove = Controller->GetViewTarget()->GetActorRotation();

}



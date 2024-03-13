// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VGP221TESTGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	//Camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCameraComponent;

	//MouseMovement
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MouseSens;

	float CamPitch;
	float CamYaw;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Horizontal / vertical camera movement
	void LookHorWithMouse(float AxisValue);
	void LookVertWithMouse(float AxisValue);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input

	//Movement Functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();
};

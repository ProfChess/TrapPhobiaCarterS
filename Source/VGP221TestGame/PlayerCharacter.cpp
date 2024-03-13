// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->GravityScale = 1.0f;

	//Create Camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	if(GetCapsuleComponent())
	{
		FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent()); //attach camera
		FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight)); //camera pos
		FirstPersonCameraComponent->bUsePawnControlRotation = true; //enable control rotation for camera
	}

	MouseSens = 0.8f;
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//Movement Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);

	//Mouse Movement Binding
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::LookHorWithMouse);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookVertWithMouse);

}

//Movement Function Def
void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{	
		//find direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//move character
		AddMovementInput(Dir, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		//Right Direction
		const FRotator Rotate = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotate.Yaw, 0);

		//Right vector
		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Move Character
		AddMovementInput(Dir, Value);
	}
}

//Jummp Func
void APlayerCharacter::Jump()
{
	bPressedJump = true;
}

void APlayerCharacter::LookHorWithMouse(float AxisValue)
{
	CamYaw += AxisValue * MouseSens;

	//Set rotation
	FRotator NewRotation = FRotator(CamPitch, CamYaw, 0.0f);
	GetController()->SetControlRotation(NewRotation);
}

void APlayerCharacter::LookVertWithMouse(float AxisValue)
{
	CamPitch += AxisValue * MouseSens;
	CamPitch = FMath::Clamp(CamPitch, -90.0f, 90.0f);

	//Set rotation
	FRotator NewRotation = FRotator(CamPitch, 0.0f, 0.0f);
	FirstPersonCameraComponent->SetRelativeRotation(NewRotation);
}

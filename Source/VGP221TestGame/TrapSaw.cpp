// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapSaw.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATrapSaw::ATrapSaw()
{
	PrimaryActorTick.bCanEverTick = true;
	//Root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Rotation point
	RotationPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationPivot"));
	RotationPivot->SetupAttachment(RootComponent);

	//Saw Mesh
	TrapSawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SawMesh"));
	TrapSawMesh->SetupAttachment(RotationPivot);

	//Defaults
	speed = 2.0f;
	bMovingForward = true;

}

// Called when the game starts or when spawned
void ATrapSaw::BeginPlay()
{
	Super::BeginPlay();
	
	//Start and End poitions
	StartLocate = RotationPivot->GetComponentLocation();
	EndLocate = StartLocate + FVector(400.0f, 0.0f, 0.0f);
	speed = 1.0f;
	bMovingForward = true;
}

// Called every frame
void ATrapSaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//move back and forth
	if (bMovingForward)
	{
		RotationPivot->SetWorldLocation(FMath::VInterpTo(RotationPivot->GetComponentLocation(), EndLocate, DeltaTime, speed));
		if (RotationPivot->GetComponentLocation().Equals(EndLocate, 1.0f))
		{
			bMovingForward = false;
		}
	}
	else
	{
		RotationPivot->SetWorldLocation(FMath::VInterpTo(RotationPivot->GetComponentLocation(), StartLocate, DeltaTime, speed));
		if (RotationPivot->GetComponentLocation().Equals(StartLocate, 1.0f))
		{
			bMovingForward = true;
		}
	}

	//rotate saw blade
	float Rotation = DeltaTime * 600.0f;
	RotationPivot->AddLocalRotation(FQuat(FRotator(0.0f, Rotation, 0.0f)));
}


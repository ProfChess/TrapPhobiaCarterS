// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapLaser.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrapLaser::ATrapLaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Laser Mesh
	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	LaserMesh->SetupAttachment(RootComponent);

	//Collisison
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapLaser::OnOverlapBegin);

	//Default Values
	speed = 2.0f;
	bMovingForward = true;

}

// Called when the game starts or when spawned
void ATrapLaser::BeginPlay()
{
	Super::BeginPlay();
	
	//Start Location
	StartLocate = GetActorLocation();

	//End Location
	EndLocate = StartLocate + FVector(0.0f, 600.0f, 0.0f);
}

// Called every frame
void ATrapLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move Laser Around (currently back and forth)
	if (bMovingForward)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), EndLocate, DeltaTime, speed));
		if (GetActorLocation().Equals(EndLocate, 1.0f))
		{
			bMovingForward = false;
		}
	}
	else
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), StartLocate, DeltaTime, speed));
		if (GetActorLocation().Equals(StartLocate, 1.0f))
		{
			bMovingForward = true;
		}
	}

}

void ATrapLaser::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Handle overlap with player or other actors here
}




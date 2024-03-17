// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapLaser.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"

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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMeshAsset(TEXT("C:/Users/carsm/OneDrive/Documents/Unreal Projects/VGP221TestGame/Content/Traps/SM_Laser.uasset"));
	if (LaserMeshAsset.Succeeded())
	{
		LaserMesh->SetStaticMesh(LaserMeshAsset.Object);
	}
	//Collisison
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapLaser::OnLaserHit);

	//Default Values
	speed = 2.0f;
	bMovingForward = true;

}

// Called when the game starts or when spawned
void ATrapLaser::BeginPlay()
{
	Super::BeginPlay();
	
	if (LaserMesh && CollisionComponent) 
	{
		//Start Location
		StartLocate = GetActorLocation();

		//End Location
		EndLocate = StartLocate + FVector(0.0f, 600.0f, 0.0f);
		speed = 2.0f;
		bMovingForward = true;

		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Laser obstacle missing components"));
	}
	
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

void ATrapLaser::OnLaserHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)

{	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "Player Hit by Laser");
	}
}





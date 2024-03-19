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

	//Collisison
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(TrapSawMesh);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrapSaw::OnSawHit);

	//Defaults
	speed = 2.0f;
	bMovingForward = true;
	HitText = "Hit by Saw Trap";

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

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
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

void ATrapSaw::OnSawHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		APawn* PlayerPawn = Cast<APawn>(OtherActor);
		APlayerController* PlayerController = PlayerPawn ? Cast<APlayerController>(PlayerPawn->GetController()) : nullptr;
		if (PlayerController)
		{
			//display text
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, HitText);
		}
	}
}


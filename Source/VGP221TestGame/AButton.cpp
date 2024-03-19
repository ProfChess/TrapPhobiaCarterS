// Fill out your copyright notice in the Description page of Project Settings.


#include "AButton.h"
#include "PlayerCharacter.h"

// Sets default values
AAButton::AAButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//button mesh
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(RootComponent);

	//collision
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(ButtonMesh);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAButton::OnButtonPressed);

	// Set default values
	WinText = "You Win!";

}

// Called when the game starts or when spawned
void AAButton::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
}

// Called every frame
void AAButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAButton::OnButtonPressed(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//check button
	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		APawn* PlayerPawn = Cast<APawn>(OtherActor);
		APlayerController* PlayerController = PlayerPawn ? Cast<APlayerController>(PlayerPawn->GetController()) : nullptr;
		if (PlayerController && PlayerController->IsInputKeyDown(EKeys::E))
		{
			//display text
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, WinText);
		}
	}
}


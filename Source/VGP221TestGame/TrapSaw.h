// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TrapSaw.generated.h"

UCLASS()
class VGP221TESTGAME_API ATrapSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapSaw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSawHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TrapSawMesh;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RotationPivot;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	FString HitText;

	FVector StartLocate;
	FVector EndLocate;
	float speed;
	bool bMovingForward;
};

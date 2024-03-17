// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* TrapSawMesh;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* RotationPivot;

	FVector StartLocate;
	FVector EndLocate;
	float speed;
	bool bMovingForward;
};

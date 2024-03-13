// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PlayerCharacter.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VGP221TESTGAME_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
};

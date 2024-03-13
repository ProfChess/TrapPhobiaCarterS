// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase()
{
	//Default pawn class
	DefaultPawnClass = APlayerCharacter::StaticClass();
}

UClass* AMyGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return DefaultPawnClass;
}

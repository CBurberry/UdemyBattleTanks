// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const 
{
	//Get pawn the player controller is currently posessing
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank!"))
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Possessing: %s"), *ControlledTank->GetName());
	}
}


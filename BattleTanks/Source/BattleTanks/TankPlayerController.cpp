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

void ATankPlayerController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) 
	{
		return;
	}

	FVector HitLocation = FVector(0.0f);	//Out param

	//Get world location through crosshair (linetrace)
	if (GetSightRayHitLocation(HitLocation)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		//If intersects with landscape
		//TODO - Tell controlled tank to aim at this point.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	//Raycast through the UI dot into the landscape

	//If landscape hit, 
		//update HitLocation and return true.
	//Else
	return false;

}

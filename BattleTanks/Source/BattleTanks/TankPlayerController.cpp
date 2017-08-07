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
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		//If intersects with landscape
		//TODO - Tell controlled tank to aim at this point.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector CameraLocationInWorld;
	FVector CameraUnitVectorInWorld;

	//"De-project" the screen position of the crosshair to a world direction.
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocationInWorld, CameraUnitVectorInWorld);
	UE_LOG(LogTemp, Warning, TEXT("Crosshair Position: %s"), *CameraUnitVectorInWorld.ToString());

	//Line trace along that look direction and see what we hit (up to a max range)

	//If landscape hit, 
		//update HitLocation and return true.
	//Else
		//return false;

	return true;

}

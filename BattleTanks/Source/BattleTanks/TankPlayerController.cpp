// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
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
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank!"));
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
		GetControlledTank()->AimAt(HitLocation);
		//If intersects with landscape
		//TODO - Tell controlled tank to aim at this point.
	}
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	FVector CameraUnitVectorInWorld;

	//"De-project" the screen position of the crosshair to a world direction.
	if (GetLookDirection(ScreenLocation, CameraUnitVectorInWorld))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *CameraUnitVectorInWorld.ToString());

		//Line trace along that look direction and see what we hit (up to a max range)
		if (GetLookVectorHitLocation(CameraUnitVectorInWorld, out_HitLocation)) 
		{
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const 
{
	FHitResult HitData;
	FVector StartPosition = PlayerCameraManager->GetCameraLocation();
	FVector EndPosition = StartPosition + (LookDirection * LineTraceRange);
	out_HitLocation = FVector(0.0f);

	bool result = GetWorld()->LineTraceSingleByChannel
		(
			HitData, 
			StartPosition, 
			EndPosition,
			ECollisionChannel::ECC_Visibility
		);
	
	//DrawDebugLine(GetWorld(), StartPosition, EndPosition, FColor(255, 0,0), false, 0.0f, 0.0f, 10.0f);
	if (result) 
	{
		out_HitLocation = HitData.Location;
	}
	return result;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const
{
	FVector CameraLocationInWorld;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocationInWorld, out_LookDirection);
}

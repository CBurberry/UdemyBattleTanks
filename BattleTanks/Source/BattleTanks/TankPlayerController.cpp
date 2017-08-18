// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("AimingComponent MISSING @ PlayerController BeginPlay"))
	}

	FoundAimingComponent(AimingComponent);

	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank))
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
	if (!GetPawn()) 
	{
		return;
	}

	FVector HitLocation = FVector(0.0f);	//Out param
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	bool bLocationHit = GetSightRayHitLocation(HitLocation);
	//Get world location through crosshair (linetrace)
	if (bLocationHit) 
	{
		AimingComponent->AimAt(HitLocation);
		//If intersects with landscape
		//TODO - Tell controlled tank to aim at this point.
	}

	//UE_LOG(LogTemp, Warning, TEXT("GetSightRayValue = %i"), bLocationHit)
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

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}

		//Subscribe our local method to the tank's death event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER RELEASE TANK"))
	StartSpectatingOnly();
}


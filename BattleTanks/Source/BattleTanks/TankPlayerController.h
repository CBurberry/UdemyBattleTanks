// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	class ATank* GetControlledTank() const;

private:

	//Start the tank moving the barrel towards the crosshair target.
	void AimTowardsCrosshair();

	//Get world location of linetrace through crosshair, true if hits landscape.
	bool GetSightRayHitLocation(FVector& out_HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333f;

	//Get the Unit vector components for X,Y,Z from the camera crosshair/dot.
	bool GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const;

	//Get the location where the ray first intersects an object on the ECC_Visibility channel, return 0 if no hit.
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const;

	//10km ray range (defualt unit in Unreal is 1cm per unit)
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
};

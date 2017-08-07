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
	
private:
	class ATank* GetControlledTank() const;

	//Start the tank moving the barrel towards the crosshair target.
	void AimTowardsCrosshair();

	//Get world location of linetrace through crosshair, true if hits landscape.
	bool GetSightRayHitLocation(FVector& out_HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
};

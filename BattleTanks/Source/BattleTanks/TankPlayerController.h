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

public:
	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
};

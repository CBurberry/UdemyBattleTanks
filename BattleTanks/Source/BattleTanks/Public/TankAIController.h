// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	class ATank* GetControlledTank() const;
	class ATank* GetPlayerTank() const;

	class ATank* ControlledTank;
	class ATank* TargetPlayer;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};

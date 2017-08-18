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
	//How close can the AI tank get.
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.0f;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

	class ATank* TankRef = nullptr;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};

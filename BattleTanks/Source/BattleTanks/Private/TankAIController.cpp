// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
#include "Public/TankAIController.h"


ATank* ATankAIController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const 
{
	//Temporary only for simple player game
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetControlledTank();
	TargetPlayer = GetPlayerTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing possession target!"), *GetName());
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Possessing %s"), *GetName(), *ControlledTank->GetName());
		if (TargetPlayer) 
		{
			UE_LOG(LogTemp, Warning, TEXT("%s has found target: %s"), *GetName(), *TargetPlayer->GetName());
		}
	}
}

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	//Assuming that the AI always has a tank and a target player.
	if (!ControlledTank || !TargetPlayer) 
	{
		return;
	}
	ControlledTank->AimAt(TargetPlayer->GetActorLocation());

}


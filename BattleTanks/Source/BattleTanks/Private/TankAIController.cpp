// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"
#include "Public/TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	ControlledTank = Cast<ATank>(GetPawn());
	TargetPlayer = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	//Assuming that the AI always has a tank and a target player.
	if (!ControlledTank || !TargetPlayer) 
	{
		return;
	}

	//Move towards player
	//TODO check radius is in cm
	MoveToActor(TargetPlayer, AcceptanceRadius);

	//Aim towards player.
	ControlledTank->AimAt(TargetPlayer->GetActorLocation());
	ControlledTank->Fire();
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"

// Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	APawn* ControlledTank = GetPawn();
	APawn* TargetPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	//Assuming that the AI always has a tank and a target player.
	if ( !ensure(ControlledTank && TargetPlayer))
	{
		return;
	}

	//Move towards player
	//TODO check radius is in cm
	MoveToActor(TargetPlayer, AcceptanceRadius);

	//Aim towards player.
	AimingComponent->AimAt(TargetPlayer->GetActorLocation());
	AimingComponent->Fire();
}


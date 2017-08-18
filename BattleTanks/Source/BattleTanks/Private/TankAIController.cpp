// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"

// Depends on movement component via pathfinding system.

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) 
{
	Super::SetPawn(InPawn);

	if (InPawn) 
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) 
		{
			return;
		}
		TankRef = PossessedTank;
		//Subscribe our local method to the tank's death event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);

	APawn* ControlledTank = GetPawn();
	APawn* TargetPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	//Assuming that the AI always has a tank and a target player.
	if ( !ensure(ControlledTank) || !ensure(TargetPlayer) || !ensure(AimingComponent))
	{
		return;
	}

	//Move towards player
	//TODO check radius is in cm
	MoveToActor(TargetPlayer, AcceptanceRadius);

	//Aim towards player.
	AimingComponent->AimAt(TargetPlayer->GetActorLocation());

	//If aiming or locked, then fire.
	if (AimingComponent->GetFiringState() == EFiringState::Locked) 
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	if (TankRef) 
	{
		UE_LOG(LogTemp, Warning, TEXT("AI RELEASE TANK"))
		TankRef->DetachFromControllerPendingDestroy();
	}
}


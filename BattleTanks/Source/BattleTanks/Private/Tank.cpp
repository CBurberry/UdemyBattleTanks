// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//No need to protect pointers as added in construction.
	//AimComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	//MoveComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}
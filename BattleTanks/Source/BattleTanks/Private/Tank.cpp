// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankAimingComponent.h"
#include "Public/Tank.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//No need to protect pointers as added in construction.
	//AimComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
	//MoveComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));
}

void ATank::BeginPlay() 
{
	Super::BeginPlay();	//Needed for BP BeginPlay event broadcast.

	AimComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::AimAt(FVector TargetLocation) 
{
	if (!ensure(AimComponent))
	{
		return;
	}
		
	AimComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::Fire() 
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds;

	if (ensure(Barrel && bIsReloaded))
	{
		//Spawn a projectile at the socket location.
		AProjectile* Shot = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);

		Shot->LaunchProjectile(LaunchSpeed);
		LastFiredTime = FPlatformTime::Seconds();
	}
}


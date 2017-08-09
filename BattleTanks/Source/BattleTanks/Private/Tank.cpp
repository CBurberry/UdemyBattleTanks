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
	AimComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector TargetLocation) 
{
	AimComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(class UTankBarrel* BarrelToSet) 
{
	if (!AimComponent) 
	{
		return;
	}
	AimComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(class UTankTurret* TurretToSet)
{
	if (!AimComponent)
	{
		return;
	}
	AimComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() 
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded) 
	{
		UE_LOG(LogTemp, Warning, TEXT("FIRE!"));

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


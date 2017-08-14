// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/pROJECTILE.H"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret) 
{
	if ( !ensure(TankBarrel && TankTurret))
	{
		return;
	}

	Barrel = TankBarrel;
	Turret = TankTurret;
}


void UTankAimingComponent::AimAt(FVector TargetLocation) 
{
	auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(),*TargetLocation.ToString(), *BarrelLocation.ToString());

	if ( !ensure(Barrel && Turret))
	{
		return;
	}

	FVector out_LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the Out launch velocity.
	bool result = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			out_LaunchVelocity,
			StartLocation,
			TargetLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
			//FFN - Make sure to define the params like this to prevent known inconsistency bug with return value.
		);

	//TODO - Currently always true even when looking at the sky, probbaly to do with out_hitlocation set to 0 when nothing in range.
	if (result) 
	{
		FVector LaunchDirectionVector = out_LaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"), *GetOwner()->GetName(), *LaunchDirectionVector.ToString());
		MoveBarrelTowards(LaunchDirectionVector);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if ( !ensure(Barrel && Turret))
	{
		return;
	}

	//Work out difference between current barrel rotation, and current aiming direction - quaternions later
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString())

	Barrel->Elevate(DeltaRotator.Pitch);	
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds;

	if (ensure(Barrel && ProjectileBlueprint && bIsReloaded))
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




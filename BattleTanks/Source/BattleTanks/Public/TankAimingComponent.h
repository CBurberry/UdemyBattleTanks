// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	//TODO - Add turret reference.

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(class UTankBarrel* BarrelToSet);
	void SetTurretReference(class UTankTurret* TurretToSet);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	void MoveBarrelTowards(FVector AimDirection);
	
};

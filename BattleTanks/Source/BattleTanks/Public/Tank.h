// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;	//TODO - find sensible default.

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFiredTime = 0.0f;

	//Selectable dropdown in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	//Local barrel reference for spawning projectile.
	class UTankBarrel* Barrel = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	class UTankAimingComponent* AimComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	class UTankMovementComponent* MoveComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	//Needed for blueprint BeginPlay event.
	virtual void BeginPlay() override;

	//Aim the gun at the target location.
	void AimAt(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
};

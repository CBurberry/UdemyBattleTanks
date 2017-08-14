// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state.
UENUM()
enum class EFiringState : uint8
{
	Locked = 0,
	Aiming,
	Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	class UTankBarrel* Barrel = nullptr;
	class UTankTurret* Turret = nullptr;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;

	//Selectable dropdown in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AProjectile> ProjectileBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	double LastFiredTime = 0.0f;

	//Is the barrel is currently rotating?
	bool IsBarrelMoving();

	FVector AimAtTargetLocation = FVector::ZeroVector;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	void AimAt(FVector WorldSpaceAim);

	void MoveBarrelTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(class UTankBarrel* TankBarrel, class UTankTurret* TankTurret);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
};

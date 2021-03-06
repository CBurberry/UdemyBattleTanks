// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	///The variables are given sensible defaults.
	UPROPERTY(EditDefaultsOnly, Category = "Aim Rotation")
	float MaxDegreesPerSecond = 20.0f;

public:
	// -1 = Max leftward movement, +1 = Max rightward movement - TODO rotation at -180/180 treated as different direction.
	void Rotate(float RelativeSpeed);
	
};

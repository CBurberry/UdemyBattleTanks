// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:

	///The below 3 variables are given sensible defaults.
	UPROPERTY(EditAnywhere, Category = "Aim Rotation")
	float MaxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Aim Rotation")
	float MaxElevationDegrees = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Aim Rotation")
	float MinElevationDegrees = 0.0f;


public:
	void Elevate(float DegreesPerSecond);
};

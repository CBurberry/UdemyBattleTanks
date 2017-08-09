// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and apply forces to the tank. Include track static mesh.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//TODO - clamp throttle value [-1, 1]
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float ThrottleValue);
	
	//Max force per track in Newtons.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxDrivingForce = 400000.0f;	//Assume 40kg tank at 1g acceleration.
};

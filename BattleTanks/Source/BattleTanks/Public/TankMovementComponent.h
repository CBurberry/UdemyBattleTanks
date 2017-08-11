// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving the tank's tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TankMovement")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "TankMovement")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet);
	
private:
	class UTankTrack* LTrack = nullptr;
	class UTankTrack* RTrack = nullptr;
	
};

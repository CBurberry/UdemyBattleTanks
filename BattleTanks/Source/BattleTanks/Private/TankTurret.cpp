// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//Clamp the input parameter.
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	//given a max rotatin speed and the frame time.
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	//move the turretl the right amount this frame
	float NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}


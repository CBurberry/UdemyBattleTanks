// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"


void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	//float Time = GetWorld()->GetTimeSeconds();
	//FString Name = GetName();

	if (!LTrack | !RTrack)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw);
	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet)
{
	if (!LTrackToSet | !RTrackToSet)
	{
		return;
	}

	LTrack = LTrackToSet;
	RTrack = RTrackToSet;

	//TODO - Prevent additive dual control speed.
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet)
{
	if (!LTrackToSet || !RTrackToSet)
	{
		return;
	}

	LTrack = LTrackToSet;
	RTrack = RTrackToSet;

	//TODO - Prevent additive dual control speed.
}


void UTankMovementComponent::IntendMoveForward(float Throw) 
{
	if (!LTrack || !RTrack)
	{
		return;
	}

	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) 
{
	if (!LTrack || !RTrack)
	{
		return;
	}
	LTrack->SetThrottle(-Throw);
	RTrack->SetThrottle(Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) 
{
	//No need to call super as we're replacing the functionality.
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float DotProduct = FVector::DotProduct(AIForwardIntention, TankForwardDirection);
	FVector CrossProduct = FVector::CrossProduct(TankForwardDirection, AIForwardIntention);

	IntendMoveForward(DotProduct);
	IntendTurnRight(CrossProduct.Z);
}

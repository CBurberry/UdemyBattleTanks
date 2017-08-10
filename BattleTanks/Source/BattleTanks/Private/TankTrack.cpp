
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankTrack.h"



void UTankTrack::SetThrottle(float ThrottleValue) 
{
	FVector ForceApplied = GetForwardVector() * ThrottleValue * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* RootLocation = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootLocation->AddForceAtLocation(ForceApplied, ForceLocation);
}

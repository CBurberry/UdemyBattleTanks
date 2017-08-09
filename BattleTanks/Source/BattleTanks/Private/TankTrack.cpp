
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankTrack.h"



void UTankTrack::SetThrottle(float ThrottleValue) 
{
	//float Time = GetWorld()->GetTimeSeconds();
	FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, ThrottleValue);
}

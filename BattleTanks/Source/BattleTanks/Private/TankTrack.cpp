
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisFunction)
{
	/*
		This should be included in general as it will otherwise call the BP TickComponent,
		not a problem here although as no BP derives this cpp class.
	*/
	Super::TickComponent(DeltaTime, TickType, ThisFunction);

	//Calculate the slippage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work-out the required acceleration this frame to correct
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetAttachmentRootActor());

	//Calculate and apply sideways force (f = ma).
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;	//Two tracks.
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float ThrottleValue) 
{
	FVector ForceApplied = GetForwardVector() * ThrottleValue * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* RootLocation = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootLocation->AddForceAtLocation(ForceApplied, ForceLocation);
}

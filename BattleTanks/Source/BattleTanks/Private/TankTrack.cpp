
// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() 
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce() 
{
	//Calculate the slippage speed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Work-out the required acceleration this frame to correct
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	//Calculate and apply sideways force (f = ma).
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;	//Two tracks.
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float ThrottleValue) 
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + ThrottleValue, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack() 
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* RootLocation = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootLocation->AddForceAtLocation(ForceApplied, ForceLocation);
}

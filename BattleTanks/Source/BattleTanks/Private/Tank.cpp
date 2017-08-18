// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount: %f, DamageToApply: %d"), DamageAmount, DamageToApply)
	CurrentHealth -= DamageToApply;
	if (CurrentHealth == 0) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has been destroyed!"), *GetName())
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float) CurrentHealth / (float) StartingHealth;
}
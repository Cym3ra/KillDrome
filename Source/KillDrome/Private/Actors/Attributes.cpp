// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Attributes.h"

#include "Characters/Enemy.h"
#include "Characters/PlayerBike.h"
#include "GameMode/BikeGameMode.h"
#include "Kismet/GameplayStatics.h"


UAttributes::UAttributes()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UAttributes::DamageTaken);

	PlayerBike = Cast<APlayerBike>(UGameplayStatics::GetPlayerPawn(this, 0));
	BikeGameMode = Cast<ABikeGameMode>(UGameplayStatics::GetGameMode(this));
	
}

void UAttributes::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f){return;}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

	if (DamagedActor == PlayerBike)
	{
		PlayerBike->SetHUDHealth();
	}
	if (AEnemy* AttackedEnemy = Cast<AEnemy>(DamagedActor))
	{
		AttackedEnemy->HandleDamage(Instigator);
	}

	if (CurrentHealth <= 0.f && BikeGameMode)
	{
		BikeGameMode->ActorDied(DamagedActor, Instigator);
	}
}

void UAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

float UAttributes::GetHealthPercent()
{
	return CurrentHealth / MaxHealth;
}

bool UAttributes::IsAlive()
{
	return CurrentHealth > 0.f;
}

void UAttributes::AddEnemiesToKill(int32 Enemies)
{
	TargetEnemiesToKill -= Enemies;
}

void UAttributes::AddEnemiesKilled(int32 Killed)
{
	TargetEnemiesKilled += Killed;
}

int32 UAttributes::GetEnemiesLeftToKill()
{
	UpdateEnemiesToKill = TargetEnemiesToKill - TargetEnemiesKilled;
	return UpdateEnemiesToKill;
}


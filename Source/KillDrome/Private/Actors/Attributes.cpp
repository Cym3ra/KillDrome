// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Attributes.h"

#include "CookerSettings.h"
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

	BikeGameMode = Cast<ABikeGameMode>(UGameplayStatics::GetGameMode(this));
	
}

void UAttributes::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f){return;}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	//CurrentHealth -= Damage;

	if (CurrentHealth <= 0.f && BikeGameMode)
	{
		BikeGameMode->ActorDied(DamagedActor);
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


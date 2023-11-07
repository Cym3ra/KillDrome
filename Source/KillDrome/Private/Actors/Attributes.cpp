// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Attributes.h"

#include "CookerSettings.h"


UAttributes::UAttributes()
{

	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UAttributes::DamageTaken);
	
}

void UAttributes::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	
}


void UAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


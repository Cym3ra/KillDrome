// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseBike.h"

#include "Actors/Attributes.h"
#include "Actors/BikeProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABaseBike::ABaseBike()
{

	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetGenerateOverlapEvents(true);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(GetMesh());

	Attributes = CreateDefaultSubobject<UAttributes>("Attributes");
	
}

void ABaseBike::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBike::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	auto Projectile = GetWorld()->SpawnActor<ABikeProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}

void ABaseBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBike::HandleDeath()
{
	
}





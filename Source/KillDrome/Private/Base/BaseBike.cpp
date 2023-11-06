// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseBike.h"
#include "Actors/BikeProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABaseBike::ABaseBike()
{

	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetGenerateOverlapEvents(true);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(GetMesh());

}

void ABaseBike::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBike::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	GetWorld()->SpawnActor<ABikeProjectile>(ProjectileClass, Location, Rotation);
	UGameplayStatics::PlaySoundAtLocation(this, LaserShotSound, GetActorLocation(), FRotator::ZeroRotator);
}

void ABaseBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





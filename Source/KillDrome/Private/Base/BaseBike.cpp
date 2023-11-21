// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseBike.h"
#include "TimerManager.h"
#include "Actors/Attributes.h"
#include "Actors/BikeProjectile.h"
#include "Actors/DeadActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


ABaseBike::ABaseBike()
{

	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetGenerateOverlapEvents(true);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(GetMesh());

	Attributes = CreateDefaultSubobject<UAttributes>("Attributes");

	SetupStimulusSource();
	
}

void ABaseBike::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBike::Fire()
{
	if (bCanFire)
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

		auto Projectile = GetWorld()->SpawnActor<ABikeProjectile>(ProjectileClass, Location, Rotation);
		Projectile->SetOwner(this);

		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABaseBike::CheckCanFire, FireRate, false);
	}
	bCanFire = false;
}

void ABaseBike::CheckCanFire()
{
	bCanFire = true;
}

void ABaseBike::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

void ABaseBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBike::HandleDeath()
{
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound,GetActorLocation(), FRotator::ZeroRotator);
	}
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), GetActorRotation());
	}

	GetWorld()->SpawnActor<ADeadActor>(DeadTargetClass, GetActorLocation(), GetActorRotation());
}

bool ABaseBike::IsAlive()
{
	return Attributes && Attributes->IsAlive();
}





// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BikeProjectile.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


ABikeProjectile::ABikeProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetGenerateOverlapEvents(true);
	// Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	// Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	// Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComp->InitialSpeed = 1200.f;
	ProjectileMovementComp->MaxSpeed = 1200.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
}


void ABikeProjectile::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentHit.AddDynamic(this, &ABikeProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, LaserShotSound, GetActorLocation(), FRotator::ZeroRotator);
	
}

void ABikeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr){return;}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		Destroy();
	}
}




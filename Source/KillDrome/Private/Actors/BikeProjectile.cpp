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

	//Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABikeProjectile::OnSphereOverlap);

	Sphere->OnComponentHit.AddDynamic(this, &ABikeProjectile::OnHit);
	
}

void ABikeProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator()) return;
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());

	Destroy();
}

void ABikeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());
}




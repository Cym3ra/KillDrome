// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DeadActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


ADeadActor::ADeadActor()
{

	PrimaryActorTick.bCanEverTick = true;

	HullMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	HullMesh->SetupAttachment(RootComponent);
	SmokeEffect = CreateDefaultSubobject<UParticleSystemComponent>("SmokeParticleComp");
	SmokeEffect->SetupAttachment(HullMesh);

	InitialLifeSpan = 5.f;
}


void ADeadActor::BeginPlay()
{
	Super::BeginPlay();
}


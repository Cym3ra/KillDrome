// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WinCheckActor.h"

#include "Characters/PlayerBike.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


AWinCheckActor::AWinCheckActor()
{

	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

}

void AWinCheckActor::BeginPlay()
{
	Super::BeginPlay();

	PlayerBike = Cast<APlayerBike>(UGameplayStatics::GetPlayerPawn(this, 0));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWinCheckActor::OnSphereOverlap);
}

void AWinCheckActor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerBike)
	{
		if (PlayerBike->CheckIfWon())
		{
			UE_LOG(LogTemp, Warning, TEXT("WON"));
		}
	}
	
}

void AWinCheckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/BaseBike.h"
#include "GameFramework/CharacterMovementComponent.h"


ABaseBike::ABaseBike()
{

	PrimaryActorTick.bCanEverTick = true;

}

void ABaseBike::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





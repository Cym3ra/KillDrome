// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"

#include "Actors/Attributes.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/BikeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

AEnemy::AEnemy()
{

}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemy::HandleDeath()
{
	Super::HandleDeath();

	TeleportTo(RespawnPoint->GetActorLocation(), GetActorRotation(), false, false);
	if (Attributes)
	{
		Attributes->ResetHealth();
	}

}

APatrolPath* AEnemy::GetPatrolPath() const
{
	return PatrolPath;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BikeAIController = Cast<ABikeAIController>(GetController());
	
}

bool AEnemy::TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck)
{
	return Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck);
}









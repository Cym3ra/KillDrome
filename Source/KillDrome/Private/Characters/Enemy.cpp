// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"
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
	Destroy();
}

APatrolPath* AEnemy::GetPatrolPath() const
{
	return PatrolPath;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//FVector WorldPatrolPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint);

	BikeAIController = Cast<ABikeAIController>(GetController());
	if ( BikeAIController)
	{
		//BikeAIController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint"), WorldPatrolPoint);

	}

}









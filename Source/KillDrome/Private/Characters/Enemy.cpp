// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"
#include "AI/BikeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemy::AEnemy()
{
	
}

void AEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	BikeAIController = Cast<ABikeAIController>(NewController);

	BikeAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BikeAIController->RunBehaviorTree(BehaviorTree);
	BikeAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
}

void AEnemy::HandleDeath()
{
	Super::HandleDeath();
	Destroy();
}

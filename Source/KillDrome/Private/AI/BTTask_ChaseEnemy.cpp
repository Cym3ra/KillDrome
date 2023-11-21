// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ChaseEnemy.h"

#include "AI/BikeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_ChaseEnemy::UBTTask_ChaseEnemy()
{
	NodeName = TEXT("Chase Enemy");
}

EBTNodeResult::Type UBTTask_ChaseEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (auto* const Controller = Cast<ABikeAIController>(OwnerComp.GetAIOwner()))
	{
		auto const BikeLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, BikeLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

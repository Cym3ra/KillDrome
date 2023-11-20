// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPathPoint.h"
#include "AI/BikeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName = TEXT("Find Path Point");
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
if (auto* const Controller = Cast<ABikeAIController>(OwnerComp.GetAIOwner()))
{
	if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
	{
		auto const Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

		if (auto* EnemyBike = Cast<AEnemy>(Controller->GetPawn()))
		{
			auto const Point = EnemyBike->GetPatrolPath()->GetPatrolPoint(Index);

			auto const GlobalPoint = EnemyBike->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
			Blackboard->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
}
	
	return EBTNodeResult::Failed;
}

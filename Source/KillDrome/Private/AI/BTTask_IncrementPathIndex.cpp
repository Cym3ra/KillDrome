// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_IncrementPathIndex.h"

#include "AI/BikeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer) : UBTTask_BlackboardBase{ObjectInitializer}
{
	NodeName =TEXT("Increment Path Index");
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if (auto* const Controller = Cast<ABikeAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const EnemyBike = Cast<AEnemy>(Controller->GetPawn()))
		{
			if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
			{
				auto const NoOfPoints = EnemyBike->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

				if (bDirectional)
				{
					if (Index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (Index == MinIndex && Direction == EDirectionType::Reverse )
					{
						Direction = EDirectionType::Forward;
					}
				}

				Blackboard->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++Index : --Index) % NoOfPoints);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}

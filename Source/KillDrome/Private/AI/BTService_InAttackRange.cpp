// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_InAttackRange.h"

#include "AI/BikeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy.h"
#include "Kismet/GameplayStatics.h"

UBTService_InAttackRange::UBTService_InAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Bike In Attack Range");
}

void UBTService_InAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	auto const * const Controller = Cast<ABikeAIController>(OwnerComp.GetAIOwner());
	auto const * const OwningBike = Cast<AEnemy>(Controller->GetPawn());

	auto const * const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), OwningBike->GetDistanceTo(Player) <= AttackRange);
}

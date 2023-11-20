// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_EnemyLocation.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "Base/BaseBike.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_EnemyLocation::UBTService_EnemyLocation()
{
	NodeName = TEXT("Update Target Location");
}

void UBTService_EnemyLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	TSubclassOf<ABaseBike> BaseBike = ABaseBike::StaticClass();
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BaseBike, Actors);
	//const FName TargetTag = OwningPawn->ActorHasTag(FName("Target"));

	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, FName("Target"), ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (auto Actor : Actors)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);

			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyLocation"), ClosestActor->GetActorLocation());
}

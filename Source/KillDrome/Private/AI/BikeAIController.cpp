// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BikeAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"

ABikeAIController::ABikeAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
	PawnSensing->SightRadius = 3000.f;
	PawnSensing->SetPeripheralVisionAngle(55.f);
	PawnSensing->bOnlySensePlayers = false;

	SetupPerceptionSystem();
	
}

void ABikeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	AEnemy* Enemy = Cast<AEnemy>(InPawn);
	if (Enemy && Enemy->GetBehaviorTree())
	{
		GetBlackboardComponent()->InitializeBlackboard(*Enemy->GetBehaviorTree()->BlackboardAsset);
		RunBehaviorTree(&*Enemy->GetBehaviorTree());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

		
	}
	
}

void ABikeAIController::BeginPlay()
{
	Super::BeginPlay();

	// if (PawnSensing)
	// {
	// 	PawnSensing->OnSeePawn.AddDynamic(this, &ABikeAIController::PawnSeen);
	// }
}

void ABikeAIController::PawnSeen(APawn* SeenPawn)
{
	CombatTarget = SeenPawn;
	if (CombatTarget)
	{
		if (LineOfSightTo(CombatTarget))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), CombatTarget->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("EnemyLocation"), CombatTarget->GetActorLocation());
		}
		else
		{
			CombatTarget = nullptr;
			GetBlackboardComponent()->ClearValue(TEXT("EnemyLocation"));
		}

	}
}

void ABikeAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 1000.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 120.f;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 1100.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ABikeAIController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

void ABikeAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const SeenPawn = Cast<APawn>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeeEnemy", Stimulus.WasSuccessfullySensed());
	}
}


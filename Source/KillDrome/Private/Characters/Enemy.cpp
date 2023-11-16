// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

AEnemy::AEnemy()
{
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Component"));
	PawnSensing->SightRadius = 3000.f;
	PawnSensing->SetPeripheralVisionAngle(55.f);
	PawnSensing->bOnlySensePlayers = false;
}

void AEnemy::CheckCombatTarget()
{
	if (!InTargetRange(CombatTarget, CombatRadius))
	{
		//Outside combat radius, lose interest
		CombatTarget = nullptr;
		EnemyState = EEnemyState::EES_Patrolling;
		MoveToTarget(PatrolTarget);
	}
	else if (!InTargetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Chasing)
	{
		// Outside attack range, chase character
		EnemyState = EEnemyState::EES_Chasing;
		MoveToTarget(CombatTarget);
	}
	else if (InTargetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Attacking)
	{
		//inside attack range, attack pawn
		EnemyState = EEnemyState::EES_Attacking;
	}
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		MoveToTarget(PatrolTarget);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyState > EEnemyState::EES_Patrolling)
	{
			CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}	
}

void AEnemy::HandleDeath()
{
	Super::HandleDeath();
	Destroy();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	BikeAIController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSeen);
	}
}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	if (Target == nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();

	return DistanceToTarget <= Radius;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (BikeAIController == nullptr || Target == nullptr) return;
	
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(100.f);
	BikeAIController->MoveTo(MoveRequest);
}

AActor* AEnemy::ChoosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}
			
	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0)
	{
		const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
		return  ValidTargets[TargetSelection];
	}
	return nullptr;
}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	if (EnemyState == EEnemyState::EES_Chasing) return;
	
	CombatTarget = SeenPawn;
	if (EnemyState != EEnemyState::EES_Attacking)
	{
		EnemyState = EEnemyState::EES_Chasing;
		MoveToTarget(CombatTarget);
	}
}

void AEnemy::HandleDamage(AController* Attacker)
{
	CombatTarget = Attacker->GetPawn();
	EnemyState = EEnemyState::EES_Chasing;
	MoveToTarget(CombatTarget);
	UE_LOG(LogTemp, Warning, TEXT("Attacker: %s"), *CombatTarget->GetName());
}


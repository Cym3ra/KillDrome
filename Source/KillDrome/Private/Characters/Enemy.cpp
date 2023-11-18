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
	if (IsOutsideCombatRadius())
	{
		LoseInterest();
		if (!IsEngaged())
		{
			StartPatrolling();
		}
	}
	else if (IsOutsideAttackRadius() && !IsChasing())
	{
		ChaseTarget();
		if (!IsEngaged())
		{
			ChaseTarget();
		}
	}
	else if (CanAttack())
	{
		//inside attack range, attack pawn
		EnemyState = EEnemyState::EES_Attacking;
		Attack();
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

	if (IsDead()) return;
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

void AEnemy::Attack()
{
	if (CombatTarget == nullptr) return;
	//EnemyState = EEnemyState::EES_Engaged;
	EnemyState = EEnemyState::EES_NoState;
	Fire();

}

void AEnemy::PawnSeen(APawn* SeenPawn)
{
	const bool bShouldChaseTarget = EnemyState != EEnemyState::EES_Dead &&
			EnemyState != EEnemyState::EES_Chasing &&
			EnemyState < EEnemyState::EES_Attacking;

	if (bShouldChaseTarget)
	{
		CombatTarget = SeenPawn;
		ChaseTarget();
	}
}

void AEnemy::LoseInterest()
{
	//Outside combat radius, lose interest
	CombatTarget = nullptr;
}

void AEnemy::StartPatrolling()
{
	EnemyState = EEnemyState::EES_Patrolling;
	MoveToTarget(PatrolTarget);
}

void AEnemy::ChaseTarget()
{
	// Outside attack range, chase character
	EnemyState = EEnemyState::EES_Chasing;
	MoveToTarget(CombatTarget);
}

bool AEnemy::IsOutsideCombatRadius()
{
	return  !InTargetRange(CombatTarget, CombatRadius);
}

bool AEnemy::IsOutsideAttackRadius()
{
	return !InTargetRange(CombatTarget, AttackRadius);
}

bool AEnemy::IsChasing()
{
	return EnemyState == EEnemyState::EES_Chasing;
}

bool AEnemy::IsAttacking()
{
	return EnemyState == EEnemyState::EES_Attacking;
}

bool AEnemy::IsDead()
{
	return EnemyState == EEnemyState::EES_Dead;
}

bool AEnemy::IsEngaged()
{
	return EnemyState == EEnemyState::EES_Engaged;
}

bool AEnemy::CanAttack()
{
	const bool bCanAttack = IsInsideAttackRadius() && !IsAttacking() && !IsDead();
	return bCanAttack;
}

bool AEnemy::IsInsideAttackRadius()
{
	return InTargetRange(CombatTarget, AttackRadius);
}

void AEnemy::HandleDamage(AController* Attacker)
{
	CombatTarget = Attacker->GetPawn();
	if (IsInsideAttackRadius())
	{
		EnemyState = EEnemyState::EES_Attacking;
	}
	else if (IsOutsideAttackRadius())
	{
		ChaseTarget();
	}
	UE_LOG(LogTemp, Warning, TEXT("Attacker: %s"), *CombatTarget->GetName());
}


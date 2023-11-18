// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "Base/BaseBike.h"
#include "Enemy.generated.h"

class AAIController;
class UPawnSensingComponent;

/**
 * 
 */
UCLASS()
class KILLDROME_API AEnemy : public ABaseBike
{
	GENERATED_BODY()

public:
	AEnemy();
	void CheckCombatTarget();
	void CheckPatrolTarget();
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath() override;
	void HandleDamage(AController* Attacker);

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void Attack();

private:

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); // Callback for OnPawnSeen in UPawnSensingComponent
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	bool CanAttack();
	bool IsInsideAttackRadius();
	
	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere)
	double AcceptanceRadius = 140.f;
	
	UPROPERTY()
	TObjectPtr<AAIController> BikeAIController;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditInstanceOnly, Category= "AI")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category= "AI")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category=Combat)
	float PatrollingSpeed = 125.f;
	UPROPERTY(EditAnywhere, Category="AI Navigation")
	float PatrolWaitMin = 4.f;
	UPROPERTY(EditAnywhere, Category="AI Navigation")
	float PatrolWaitMax = 8.f;
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category=Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category=Combat)
	float AttackMax = 1.f;
	UPROPERTY(EditAnywhere, Category=Combat)
	float ChasingSpeed = 300.f;

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;
};

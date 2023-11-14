// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseBike.h"
#include "Enemy.generated.h"

class UBehaviorTree;
class ABikeAIController;

/**
 * 
 */
UCLASS()
class KILLDROME_API AEnemy : public ABaseBike
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void PossessedBy(AController* NewController) override;
	virtual void HandleDeath() override;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return BehaviorTree;}

protected:

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ABikeAIController> BikeAIController;
	
	
};

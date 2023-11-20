// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PatrolPath.h"
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
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath() override;
	APatrolPath* GetPatrolPath() const;
	

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return BehaviorTree;}

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<ABikeAIController> BikeAIController;

	UPROPERTY(EditAnywhere, Category= "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, Category= "Behavior Tree", meta=(AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector PatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess = "true"))
	APatrolPath* PatrolPath;

};

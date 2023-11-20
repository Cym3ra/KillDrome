// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_EnemyLocation.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API UBTService_EnemyLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_EnemyLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

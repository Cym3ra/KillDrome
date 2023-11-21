// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_InAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API UBTService_InAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_InAttackRange();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess = "true"))
	float AttackRange = 500.f;
	
};

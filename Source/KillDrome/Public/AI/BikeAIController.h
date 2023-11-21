// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BikeAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UPawnSensingComponent;
/**
 * 
 */
UCLASS()
class KILLDROME_API ABikeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABikeAIController();
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, Category= "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); // Callback for OnPawnSeen in UPawnSensingComponent

private:

	class UAISenseConfig_Sight* SightConfig;

	void SetupPerceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HUD/MainOverlay.h"
#include "BikeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API ABikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	void ActorDied(AActor* DeadActor, AController* Killer);
	void LoadLevelDelay();

	
	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:

	UPROPERTY()
	class APlayerBike* PlayerBike;

	UPROPERTY()
	class ABikePlayerController* BikePlayerController;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float StartDelay = 3.f;
	float LoadDelay = 2.f;
	
	void HandleGameStart();
	
	int32 GetTargetEnemyCount();
	

	UPROPERTY()
	UMainOverlay* MainOverlay;
};

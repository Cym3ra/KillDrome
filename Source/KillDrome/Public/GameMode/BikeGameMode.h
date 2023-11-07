// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BikeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API ABikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	UPROPERTY()
	class APlayerBike* PlayerBike;

	UPROPERTY()
	class ABikePlayerController* BikePlayerController;

	float Startdelay = 3.f;

	void HandleGameStart();
	
};

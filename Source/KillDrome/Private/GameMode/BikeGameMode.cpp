// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BikeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerBike.h"
#include "Characters/Enemy.h"
#include "GameMode/BikePlayerController.h"


void ABikeGameMode::ActorDied(AActor* DeadActor, AController* Killer)
{
	if (DeadActor == PlayerBike)
	{
		PlayerBike->HandleDeath();
	}
	else if (AEnemy* KilledEnemy = Cast<AEnemy>(DeadActor))
	{
		if (Killer == BikePlayerController)
		{
			PlayerBike->AddEnemiesKilled(1);
			PlayerBike->AddEnemiesToEliminate();
		}
		KilledEnemy->HandleDeath();
	}
}

void ABikeGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//HandleGameStart();  Uncomment when its time to build game

	// Can add these to HandleGameStart when the game is ready to play
	PlayerBike = Cast<APlayerBike>(UGameplayStatics::GetPlayerPawn(this, 0));
	BikePlayerController = Cast<ABikePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

float ABikeGameMode::GetRemainingTime() const
{
	return TimeRemaining;
}

void ABikeGameMode::HandleGameStart()
{
	StartGame();
	
	if (BikePlayerController)
	{
		BikePlayerController->SetPlayerEnabledState(false);

		// Timer that enables player input when the timer is done, after Startdelay time
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(BikePlayerController, &ABikePlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 ABikeGameMode::GetTargetEnemyCount()
{
	//TODO check enemies killed vs enemies needed to kill
	return 0;
}

void ABikeGameMode::UpdateGameTimer()
{
	
}

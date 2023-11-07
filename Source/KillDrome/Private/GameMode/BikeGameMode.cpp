// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BikeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerBike.h"
#include "Characters/Enemy.h"
#include "GameMode/BikePlayerController.h"


void ABikeGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerBike)
	{
		PlayerBike->HandleDeath();
		if (BikePlayerController)
		{
				BikePlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (AEnemy* KilledEnemy = Cast<AEnemy>(DeadActor))
	{
		KilledEnemy->HandleDeath();
	}
}

void ABikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	//HandleGameStart();

	// Can add these to HandleGameStart when the game is ready to play
	PlayerBike = Cast<APlayerBike>(UGameplayStatics::GetPlayerPawn(this, 0));
	BikePlayerController = Cast<ABikePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
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
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, Startdelay, false);
	}
}

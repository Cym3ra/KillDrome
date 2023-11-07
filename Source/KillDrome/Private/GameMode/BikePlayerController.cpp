// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BikePlayerController.h"

void ABikePlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
}

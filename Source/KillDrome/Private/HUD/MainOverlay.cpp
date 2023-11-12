// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UMainOverlay::SetEnemiesToKill(int32 ToKill)
{
	if (EnemiesRemainingText)
	{
		EnemiesRemainingText->SetText(FText::FromString(FString::Printf(TEXT("%d kills left"), ToKill)));
	}
}

void UMainOverlay::SetEnemiesKilled(int32 Killed)
{
	if (Enemies)
	{
		Enemies->SetText(FText::FromString(FString::Printf(TEXT("%d kills"), Killed)));
	}
}


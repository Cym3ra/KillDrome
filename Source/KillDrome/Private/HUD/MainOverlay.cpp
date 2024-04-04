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

void UMainOverlay::SetCountDownText(float CountDownTime)
{
	if (TimerText)
	{
		int32 Minutes = FMath::FloorToInt(CountDownTime / 60.f);
		int32 Seconds = CountDownTime - Minutes * 60;

		FString CountDownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		TimerText->SetText(FText::FromString(CountDownText));
	}
}

void UMainOverlay::SetWinText()
{
	if (WinText)
	{
		WinText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainOverlay::HideWinText()
{
	if (WinText)
	{
		WinText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainOverlay::SetGameOverText()
{
	if (LoseText && ReloadText)
	{
		LoseText->SetVisibility(ESlateVisibility::Visible);
		ReloadText->SetVisibility(ESlateVisibility::Visible);
	}
}


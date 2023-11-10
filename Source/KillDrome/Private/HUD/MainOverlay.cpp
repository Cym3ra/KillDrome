// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MainOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMainOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UMainOverlay::SetPointsText(int32 Points)
{
	if (PointsText)
	{
		PointsText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Points)));
	}
}

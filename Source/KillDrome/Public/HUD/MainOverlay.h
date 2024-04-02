// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainOverlay.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API UMainOverlay : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealthBarPercent(float Percent);
	void SetEnemiesToKill(int32 ToKill);
	void SetEnemiesKilled(int32 Killed);
	void SetCountDownText(float CountDownTime);
	void SetWinText();
	void HideWinText();

private:
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TimerText;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Enemies;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* EnemiesRemainingText;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* WinText;

};

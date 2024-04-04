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
	void SetGameOverText();

private:
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Enemies;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* EnemiesRemainingText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* WinText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* LoseText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ReloadText;
};

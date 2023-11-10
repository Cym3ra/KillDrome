// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	void SetPointsText(int32 Points);

private:
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* PointsText;
};

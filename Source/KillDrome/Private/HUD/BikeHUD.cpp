// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BikeHUD.h"

#include "GameMode/BikePlayerController.h"
#include "HUD/MainOverlay.h"

void ABikeHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController && MainOverlayClass)
		{
			MainOverlay = CreateWidget<UMainOverlay>(PlayerController, MainOverlayClass);
			MainOverlay->AddToViewport();
		}
	}
}

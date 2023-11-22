// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BikeHUD.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API ABikeHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Overlay", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class UMainOverlay> MainOverlayClass;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UMainOverlay* MainOverlay;

public:
	FORCEINLINE UMainOverlay* GetBikeOverlay() const { return MainOverlay;}
};

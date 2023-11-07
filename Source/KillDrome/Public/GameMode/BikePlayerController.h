// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BikePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KILLDROME_API ABikePlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	void SetPlayerEnabledState(bool bPlayerEnabled);
};

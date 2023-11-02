// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseBike.generated.h"


UCLASS()
class KILLDROME_API ABaseBike : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseBike();
	virtual void Tick(float DeltaTime) override;

	
protected:

	virtual void BeginPlay() override;


private:
	



};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/BaseBike.h"
#include "InputActionValue.h"
#include "PlayerBike.generated.h"

class UInputMappingContext;
class UInputAction;


/**
 * 
 */
UCLASS()
class KILLDROME_API APlayerBike : public ABaseBike
{
	GENERATED_BODY()

public:
	APlayerBike();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input)
	UInputMappingContext* VehicleContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input)
	UInputAction* ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= Input)
	UInputAction* SteeringAction;

	void ApplyThrottle(const FInputActionValue& Value);
	void ApplySteering(const FInputActionValue& Value);

private:
	
	
};

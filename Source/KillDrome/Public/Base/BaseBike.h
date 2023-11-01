// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseBike.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class KILLDROME_API ABaseBike : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseBike();
	virtual void Tick(float DeltaTime) override;
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KILLDROME_API UAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributes();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category= "Attributes")
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, Category= "Attributes")
	float CurrentHealth = 0.f;
	
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator,  AActor* DamageCauser);
	
	class ABikeGameMode* BikeGameMode;
	

		
};

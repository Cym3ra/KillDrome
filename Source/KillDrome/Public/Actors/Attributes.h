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
	float GetHealthPercent();
	void AddEnemiesToKill(int32 Enemies);
	void AddEnemiesKilled(int32 Killed);
	int32 GetEnemiesLeftToKill();

	FORCEINLINE int32 GetEnemiesToKill() const {return TargetEnemiesToKill;}
	FORCEINLINE int32 GetEnemiesKilled() const {return TargetEnemiesKilled;}
	
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
	
	UPROPERTY()
	class APlayerBike* PlayerBike;

	UPROPERTY(EditAnywhere, Category="Enemies")
	int32 TargetEnemiesToKill;

	UPROPERTY(VisibleAnywhere,Category="Enemies")
	int32 TargetEnemiesKilled = 0;

	int32 UpdateEnemiesToKill;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseBike.generated.h"

class UAttributes;

UCLASS()
class KILLDROME_API ABaseBike : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseBike();
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath();

protected:

	virtual void BeginPlay() override;
	void Fire();
	
	UPROPERTY(VisibleAnywhere)
	UAttributes* Attributes;



private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class ABikeProjectile> ProjectileClass;

	bool bCanFire = true;
	void CheckCanFire();

	FTimerHandle FireRateTimerHandle;
	float FireRate = 0.5f;

};

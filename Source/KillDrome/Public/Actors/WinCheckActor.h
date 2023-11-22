// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinCheckActor.generated.h"

class USphereComponent;

UCLASS()
class KILLDROME_API AWinCheckActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWinCheckActor();
	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

private:

	UPROPERTY()
	class APlayerBike* PlayerBike;
	
};

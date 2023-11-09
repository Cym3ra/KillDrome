// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeadActor.generated.h"

class UParticleSystemComponent;

UCLASS()
class KILLDROME_API ADeadActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ADeadActor();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(Category="MeshComponent", EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* HullMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystemComponent> SmokeEffect;
};

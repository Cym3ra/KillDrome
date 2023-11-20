// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PatrolPath.h"


APatrolPath::APatrolPath()
{

	PrimaryActorTick.bCanEverTick = false;

}

FVector APatrolPath::GetPatrolPoint(int const Index) const
{
	return  PatrolPoints[Index];
}

int APatrolPath::Num() const
{
	return  PatrolPoints.Num();
}



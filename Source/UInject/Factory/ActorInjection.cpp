// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInjection.h"


void AActorInjection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TriggeredOnConstruction.Broadcast(this);
}


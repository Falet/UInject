// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorInjection.generated.h"

UCLASS()
class UINJECT_API AActorInjection : public AActor
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	DECLARE_EVENT_OneParam(AActorInjection, FTriggeredOnConstruction, AActorInjection*);
	FTriggeredOnConstruction TriggeredOnConstruction;
};


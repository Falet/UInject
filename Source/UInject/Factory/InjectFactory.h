// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InjectFactory.generated.h"

class UDiContainer;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UINJECT_API UInjectFactory : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UDiContainer* _container;

public:
	void SetContainer(UDiContainer* container);
};

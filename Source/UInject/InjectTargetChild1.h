// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InjectTarget.h"
#include "InjectTargetChild1.generated.h"

/**
 * 
 */
UCLASS()
class UINJECT_API AInjectTargetChild1 : public AInjectTarget
{
private:
	GENERATED_BODY()
public:
	
	DECLARE_DELEGATE(FTestDelegate)

protected:
	virtual void BeginPlay() override;
	const static AInjectTarget* Prop;

public:
	void Log();
};

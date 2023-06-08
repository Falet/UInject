// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InjectTargetChild1.h"
#include "MyInterface.h"
#include "InjectTargetChild2.generated.h"



/**
 * 
 */
UCLASS()
class UINJECT_API AInjectTargetChild2 : public AInjectTargetChild1, public IMyInterface
{
public:
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void PostActorCreated() override;
	virtual void PostLoad() override;
	virtual void TestTestTest_Implementation() override;
	virtual void asd1_Implementation() override;
	virtual void PreInitializeComponents() override;

private:
	GENERATED_BODY()
public:
	int32 TestProp5 = 123;
	DECLARE_EVENT(AInjectTargetChild2, FEventTest)
	FEventTest dfhdfh;
protected:
	virtual void BeginPlay() override;
};

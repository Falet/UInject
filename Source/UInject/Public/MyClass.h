// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InjectMacros.h"
#include "MyStruct.h"
#include "UInject/EventInject/EventHandler.h"
#include "UObject/Object.h"
#include "MyClass.generated.h"

/**
 * 
 */
UCLASS()
class UINJECT_API AMyClass : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	DECLARE_MULTICAST_DELEGATE_OneParam(EventTest, AActor*);
	TEventHandler<AMyClass, EventTest> testInjectEvent;
	
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorInjectionSpawned, AActor*);
	FOnActorInjectionSpawned::FDelegate delegateTest;
	
	UFUNCTION()
	void Test(AActor* af);
	
	UINJECTFUNC()
	void TestEventCPP(TPublicEvent<TMulticastDelegate<void(AActor*)>>* PublicEvent, FMyStruct struc, AActor* ac);
};

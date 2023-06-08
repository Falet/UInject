// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UInject/BaseInjectStruct.h"
#include "UInject/TestEvent/EventHandler.h"
#include "ActorInjection.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggeredOnConstructionDelegateDynamic);


UCLASS()
class UINJECT_API AActorInjection : public AActor
{
	GENERATED_BODY()

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	DECLARE_EVENT_OneParam(AActorInjection, FTriggeredOnConstruction, AActorInjection*);
	TEventHandler<AActorInjection, FTriggeredOnConstruction> test;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggeredOnConstructionDelegateDynamicParam, AActorInjection*, actor);
	
	DECLARE_DYNAMIC_DELEGATE(FTriggeredOnConstructionDelegateDynamicOne);
	FTriggeredOnConstructionDelegateDynamicOne dynamicasd;
	TEventHandler<AActorInjection, FTriggeredOnConstructionDelegateDynamicParam> testDynamyc;
	//DynamicEvent<AActorInjection, FTriggeredOnConstructionDelegateDynamic> test2;
	DECLARE_MULTICAST_DELEGATE_OneParam(FTriggeredOnConstructionDelegate, AActorInjection*)
	TEventHandler<AActorInjection, FTriggeredOnConstructionDelegate> test1;
	FTriggeredOnConstructionDelegate test123;
	DECLARE_DELEGATE_OneParam(FTriggeredOnConstructionDelegate1, AActorInjection*)
	FTriggeredOnConstructionDelegate1 rthrth;
	UPROPERTY(BlueprintCallable)
	FTriggeredOnConstructionDelegateDynamicParam Delegatea;
	//FBaseInjectStruct strufg = FBaseInjectStruct(Delegatea);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBaseInjectStruct testStruct;
protected:
	virtual void BeginPlay() override;
};


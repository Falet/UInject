// Fill out your copyright notice in the Description page of Project Settings.


#include "MyClass.h"

#include "InjectClassHolder.h"
#include "InjectFunction.h"

TMap<FString, InjectClass*> InjectClassHolder::InjectClasses;

void AMyClass::BeginPlay()
{
	Super::BeginPlay();
	auto inject = InjectClassHolder::GetInjectClassByName("AMyClass");
	
	FLocals local1;
	FLocals local2;
	FLocals local3;
	auto x = testInjectEvent.GetPublicEvent();
	local1.Value = &x;
	local1.Next = &local2;
	local2.Value = new FMyStruct();
	local2.Next = &local3;
	local3.Value = NewObject<AActor>();
	
	FFrameUInject frame(&local1);
	delegateTest = FOnActorInjectionSpawned::FDelegate::CreateUObject(this, &AMyClass::Test);
	
	inject->InjectFunc->CallInjectFunction(this, frame);
	
	//x->Add(delegateTest);
	testInjectEvent.Event.Broadcast(this);
}

void AMyClass::Test(AActor* af)
{
	
}

void AMyClass::TestEventCPP(TPublicEvent<TMulticastDelegate<void(AActor*)>>* PublicEvent, FMyStruct struc, AActor* ac)
{
	PublicEvent->Add(delegateTest);
	struc.i = 856856;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorInjection.h"

#include "UInject/InjectTargetChild1.h"


void AActorInjection::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AActorInjection::BeginPlay()
{
	Super::BeginPlay();

	TArray<FProperty*> Properties;
	UClass* claset = GetClass();
	auto name = claset->PropertyLink->GetName();
	for (TFieldIterator<FProperty> PropertyIterator(GetClass()); PropertyIterator; ++PropertyIterator)
	{
		FProperty* Property = *PropertyIterator;
		Properties.Add(Property);
	}
	AInjectTargetChild1* sdf1 = GetWorld()->SpawnActor<AInjectTargetChild1>();
	//sdf1->TestEventCPP(test1.GetPublicEvent());
	//sdf1->TestEvent(test2);
	//sdf1->TestEvent1(test123);
}



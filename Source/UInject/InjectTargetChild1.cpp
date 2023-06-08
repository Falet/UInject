// Fill out your copyright notice in the Description page of Project Settings.


#include "InjectTargetChild1.h"

void AInjectTargetChild1::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->SpawnActor<ADiContainer>()->Register<AInjectTarget*>(this);
}

void AInjectTargetChild1::Log()
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *GetName());
}
//void AInjectTargetChild1::TestEvent(AActorInjection::FTriggeredOnConstructionDelegateDynamic value){}

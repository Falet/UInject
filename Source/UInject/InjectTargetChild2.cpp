// Fill out your copyright notice in the Description page of Project Settings.


#include "InjectTargetChild2.h"

void AInjectTargetChild2::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();
}

void AInjectTargetChild2::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
}

void AInjectTargetChild2::PostActorCreated()
{
	Super::PostActorCreated();
}

void AInjectTargetChild2::PostLoad()
{
	Super::PostLoad();
}

void AInjectTargetChild2::TestTestTest_Implementation()
{
	IMyInterface::TestTestTest_Implementation();
	
}

void AInjectTargetChild2::asd1_Implementation()
{
	IMyInterface::asd1_Implementation();
	
}

void AInjectTargetChild2::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	UE_LOG(LogTemp, Display, TEXT("%s"), *GetClass()->GetName());
}

void AInjectTargetChild2::BeginPlay()
{
	Super::BeginPlay();
	dfhdfh.Broadcast();
	//GetWorld()->SpawnActor<ADiContainer>()->Register<AInjectTargetChild1*>(this);
}

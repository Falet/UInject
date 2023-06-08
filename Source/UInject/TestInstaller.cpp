// Fill out your copyright notice in the Description page of Project Settings.


#include "TestInstaller.h"

#include "InjectTargetChild2.h"
#include "MyInterface.h"
#include "Async/Async.h"
#include "Container/UDiContainer.h"


UTestInstaller::UTestInstaller()
{
	bWantsInitializeComponent = true;
}

void UTestInstaller::InitializeComponent()
{
	Super::InitializeComponent();
}

void UTestInstaller::InstallBindingsInCPP(UDiContainer* actorContainer)
{
	AInjectTargetChild2* sdf1 = GetWorld()->SpawnActor<AInjectTargetChild2>();
	actorContainer->BindUInterface<IMyInterface>().To<AInjectTargetChild2>().From(sdf1);
	actorContainer->BindUClass<AInjectTargetChild1>().From(sdf1);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "InjectTarget.h"

#include "Contexts/ActorContext.h"

void AInjectTarget::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	auto comps = GetComponents();
}

void AInjectTarget::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
}

// Sets default values
AInjectTarget::AInjectTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("AInteractiveActor_SceneComponent"));
	//SetRootComponent(SceneComponent);
	ActorContext = CreateDefaultSubobject<UActorContext>(FName("ActorContext4124"));
}

// Called when the game starts or when spawned
void AInjectTarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInjectTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInjectTarget::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();
	auto dfg = GetComponents();
}


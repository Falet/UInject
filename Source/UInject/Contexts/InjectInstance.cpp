// Fill out your copyright notice in the Description page of Project Settings.


#include "InjectInstance.h"
#include "SceneContext.h"
#include "Kismet/GameplayStatics.h"


UInjectInstance::UInjectInstance()
{
	ActorSpawnedDelegate = FOnActorSpawned::FDelegate::CreateUObject(this, &UInjectInstance::OnActorSpawned);
}

void UInjectInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	
	if (OldWorld || ActorSpawnedDelegateHandle.IsValid())
	{
		OldWorld->RemoveOnActorPreSpawnInitialization(ActorSpawnedDelegateHandle);
	}
	SceneContext = Cast<ASceneContext>(UGameplayStatics::GetActorOfClass(NewWorld, ASceneContext::StaticClass()));
	if (SceneContext)
	{
		SceneContext->PrimaryInitializeComponents();
		ActorSpawnedDelegateHandle = NewWorld->AddOnActorPreSpawnInitialization(ActorSpawnedDelegate);
	}
}

void UInjectInstance::OnActorSpawned(AActor* InActor)
{
	if (SceneContext)
	{
		SceneContext->PreInitializeActor(InActor);
	}
}
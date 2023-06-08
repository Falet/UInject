// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SceneContext.h"
#include "CoreMinimal.h"
#include "UInject/Installer.h"
#include "Kismet/GameplayStatics.h"
#include "InjectInstance.generated.h"

/**
 * 
 */
UCLASS()
class UINJECT_API UInjectInstance : public UGameInstance
{
public:
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;

private:
	UInjectInstance();
	void OnActorSpawned(AActor* InActor);

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UInstaller*> _installers;

	TMap<FString , void*> _container;

	FOnActorSpawned::FDelegate ActorSpawnedDelegate;
	FDelegateHandle ActorSpawnedDelegateHandle;

	UPROPERTY()
	ASceneContext* SceneContext;
};

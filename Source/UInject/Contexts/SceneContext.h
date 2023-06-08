// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneContext.generated.h"

class UInstaller;
class UDiContainer;
class AActorInjection;
class UActorContext;

UCLASS()
class UINJECT_API ASceneContext : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void PostLoad() override;
	virtual void PostActorCreated() override;

	ASceneContext();
	void RegisterBinding();
	void RegisterWorldBindings(TArray<UActorContext*>& actorsForInjection);
	void Injection(TArray<UActorContext*>& actorsForInjection);
	void PrimaryInitializeComponents();
	void PreInitializeActor(AActor* InActor);
	UActorContext* GetActorContext(AActor* InActor);
	void RegisterActor(AActor* InActor);
	void OnConstructionActor(AActorInjection* InActor);
	
private:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorInjectionSpawned, AActorInjection*);
	TArray<UActorContext*> _actorContexts;
	FOnActorInjectionSpawned::FDelegate ActorOnConstructionDelegate;
	
	UPROPERTY()
	UDiContainer* _container;
	
	UPROPERTY()
	TArray<UInstaller*> _installers = TArray<UInstaller*>();
	
	virtual void PreInitializeComponents() override;
};

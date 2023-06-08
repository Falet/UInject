// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneContext.h"
#include "Components/ActorComponent.h"
#include "UInject/Installer.h"
#include "ActorContext.generated.h"

UCLASS(ClassGroup=(Utility, Common), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UINJECT_API UActorContext : public UActorComponent
{
private:
	GENERATED_BODY()

public:
	UActorContext();

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	
public:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	void RegisterBindings(UDiContainer* worldContainer);
	void RegisterChild(UActorContext* child);
	UActorComponent* FindDefaultComponentByClass(TSubclassOf<AActor> InActorClass,
	                                             TSubclassOf<UActorComponent> InComponentClass);
	void Injection();

private:
	UPROPERTY()
	ASceneContext* _sceneContext;
	
	//TSharedRef<UInstaller*> sdgsdg;

	UPROPERTY()
	UDiContainer* _container;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UInstaller>> _installersTest = TArray<TSubclassOf<UInstaller>>();
};

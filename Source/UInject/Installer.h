// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Installer.generated.h"


struct FMyStruct;
class UDiContainer;

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Utility, Common), meta=(BlueprintSpawnableComponent))
class UINJECT_API UInstaller : public UActorComponent
{
private:
	GENERATED_BODY()
public:
	UInstaller();
	
	virtual void InstallBindingsInCPP(UDiContainer* actorContainer);
	
	UFUNCTION(BlueprintImplementableEvent)
	void InstallBindingsInBlueprint(UDiContainer* actorContainer);

	UFUNCTION()
	void Test(FMyStruct gdfg);
};

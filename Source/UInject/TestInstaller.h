// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Installer.h"
#include "Async/Async.h"
#include "TestInstaller.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UINJECT_API UTestInstaller : public UInstaller
{
public:
	UTestInstaller();

	virtual void InitializeComponent() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UObject*> TargetObject;
	
	virtual void InstallBindingsInCPP(UDiContainer* actorContainer) override;
private:
	GENERATED_BODY()
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Native.h"
#include "MyInterface.generated.h"

// This class does not need to be modified. 
UINTERFACE(BlueprintType)
class UMyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UINJECT_API IMyInterface
{
private:
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void asd1();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TestTestTest();
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InjectClass.h"

class InjectClassHolder
{
	InjectClassHolder();
	static TMap<FString, InjectClass*> InjectClasses;
	
public:
	static void RegisterInjectClass(InjectClass* injClass)
	{
		InjectClasses.Add(injClass->Name, injClass);
	}

	static InjectClass* GetInjectClassByName(FString name)
	{
		return InjectClasses.FindRef(name);
	}

	static TArray<InjectClass*> GetAllInjectClassByName()
	{
		TArray<InjectClass*> injectClasses;
		InjectClasses.GenerateValueArray(injectClasses);
		return injectClasses;
	}
};

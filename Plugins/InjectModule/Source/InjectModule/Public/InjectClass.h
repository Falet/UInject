// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class InjectClassHolder;
class InjectFunction;

class InjectClass
{
public:
	InjectClass(const FString& Name, const InjectFunction* InjectFunc)
		: Name(Name),
		  InjectFunc(InjectFunc)
	{
	}
	const FString Name;
	const InjectFunction* InjectFunc;
};

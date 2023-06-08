// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define UINJECTFUNC()

#define DECLARE_INJECT_FUNC(func) static void func( UObject* Context, FFrameUInject& Stack)

#define DEFINE_INJECT_FUNC(func) void func( UObject* Context, FFrameUInject& Stack)

#define GET_UINJECT_OBJECT_REF(ParamType, ParamName)		\
	ParamType* ParamName = Stack.GetObjectRef<ParamType>();	\

#define GET_UINJECT_OBJECT(ParamType, ParamName) \
	ParamType ParamName;						\
	Stack.GetObject<ParamType>(&ParamName);	\






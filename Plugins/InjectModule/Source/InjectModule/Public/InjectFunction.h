// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class InjectClass;
class InjectClassHolder;

struct FLocals
{
	void* Value;
	FLocals* Next;
};

struct FFrameUInject
{
	explicit FFrameUInject(FLocals* Start)
		: Start(Start),
		  Current(Start)
	{
	}
	
private:
	FLocals* Start;
	FLocals* Current;
	
public:
	template<typename TInjectType>
	FORCEINLINE void GetObject(void*const result)
	{
		uint8 size = sizeof(TInjectType);
		FMemory::Memcpy(result, Current->Value, size);
		if (Current->Next)
		{
			Current = Current->Next;
		}
		else
		{
			Current = Start;
		}
	}

	template<typename TInjectType>
	FORCEINLINE TInjectType* GetObjectRef()
	{
		TInjectType* result = (TInjectType*)Current->Value;
		
		if (Current->Next)
		{
			Current = Current->Next;
		}
		else
		{
			Current = Start;
		}
		
		return result;
	}
};

typedef void (*FNativeInjectFuncPtr)(UObject* Context, FFrameUInject& Stack);

struct FNameNativePtrInjectFunction
{
	FNameNativePtrInjectFunction(const char* NameUTF8, FNativeInjectFuncPtr Pointer)
		: NameUTF8(NameUTF8),
		  Pointer(Pointer)
	{
	}

	const char* NameUTF8;
	FNativeInjectFuncPtr Pointer;
};

class InjectFunction
{
public:
	InjectFunction(const FNameNativePtrInjectFunction* InjectFunc, const FString* Properties, int Size)
		: InjectFunc(InjectFunc),
		  Properties(Properties),
		  Size(Size)
	{
		Array = new TArray<FString>();
		for (int i = 0; i < Size; i++)
		{
			Array->Add(Properties[i]);
		}
	}

	TArray<FString>* GetProperties() const
	{
		return Array;
	}
	
	void CallInjectFunction(UObject* context, FFrameUInject& Stack) const
	{
		InjectFunc->Pointer(context, Stack);
	}
private:
	const FNameNativePtrInjectFunction* InjectFunc;
	const FString* Properties;
	const int Size;
	TArray<FString>* Array;
	friend InjectClass;
};
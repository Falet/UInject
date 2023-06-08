#include "UDiContainer.h"

#include "UInject/Factory/InjectFactory.h"

void** UDiContainer::FindObjectInContainer(FProperty* fProperty)
{
	FString outName = FString();
	FString nameInject = fProperty->GetCPPType(&outName,0);
	FString resultInjectName;
	if (outName.IsEmpty() == false)
	{
		resultInjectName = nameInject + outName;
	}
	else
	{
		resultInjectName = nameInject;
	}
	if (_container.Num() == 0)
	{
		return nullptr;
	}
	void** checkRef = _container.Find(resultInjectName);
	if (checkRef == nullptr)
	{
		checkRef = _container.Find(outName);
		if (checkRef == nullptr)
		{
			return checkRef;
		}
	}
	return checkRef;
}

void** UDiContainer::GetInjectObject(FProperty* fProperty)
{
	if (void** ptrOnObject = FindObjectInContainer(fProperty))
	{
		return ptrOnObject;
	}
	if (PreviousContainer)
	{
		return PreviousContainer->GetInjectObject(fProperty);
	}
	return nullptr;
}

bool UDiContainer::CheckDuplicateInContainers(FString className)
{
	if (_container.Num() > 0 && _container.Find(className))
	{
		UE_LOG(LogTemp, Error, TEXT("Class %s already added"), *className);
		return false;
	}
	
	if(PreviousContainer)
	{
		return PreviousContainer->CheckDuplicateInContainers(className);
	}

	return true;
}

void UDiContainer::BindClass(UClass* classReflectionData, UObject* classObj)
{
	if (classReflectionData && classObj)
	{
		if (classReflectionData->IsChildOf(classObj->GetClass()))
		{
			FString className = classReflectionData->GetPrefixCPP() + classReflectionData->GetName() + "*";
			if (CheckDuplicateInContainers(className))
			{
				_container.Add(className, classObj);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Class is NULL"));
	}
}

void UDiContainer::BindInterface(TSubclassOf<UInterface> interfaceUClass, UObject* interfaceObj)
{
	if (interfaceUClass && interfaceObj)
	{
		UClass* inter = interfaceUClass.Get();
		if (interfaceObj->GetClass()->ImplementsInterface(inter))
		{
			TScriptInterface<IInterface>* interWrapper = new TScriptInterface<IInterface>();
			interWrapper->SetObject(interfaceObj);
			interWrapper->SetInterface((IInterface*)interfaceObj->GetInterfaceAddress(inter));
			FString className = "<I" + interfaceUClass->GetName() + ">";
			if (CheckDuplicateInContainers(className))
			{
				_container.Add(className, interWrapper);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Error type: Reference object isn't %s"), *interfaceUClass->GetName());
		} 
	}
}

void UDiContainer::BindFactory(TSubclassOf<UInjectFactory> factoryUClass, UInjectFactory* factoryObj)
{
	if (factoryUClass)
	{
		UClass* factory = factoryUClass.Get();
		if (factoryObj == nullptr)
		{
			factoryObj = Cast<UInjectFactory>(factory->GetDefaultObject());
		}
		if (factoryObj->GetClass()->IsChildOf(factory))
		{
			factoryObj->SetContainer(this);
			FString className = factory->GetPrefixCPP() + factory->GetName() + "*";
			if (CheckDuplicateInContainers(className))
			{
				_container.Add(className, factoryObj);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Error type: Reference object isn't %s"), *factory->GetName());
		} 
	}
}

//void ADiContainer::BindStruct(UScriptStruct* structReflectionData, FBaseInjectStruct& structObj)
//{
//	if (structReflectionData)
//	{
//		if (structReflectionData->IsChildOf(structObj.StaticStruct()))
//		{
//			void* testStruct = (uint8*)FMemory_Alloca(structReflectionData->PropertiesSize);
//			structReflectionData->InitializeStruct(testStruct, 1);
//			structReflectionData->PostInitProperties();
//			container.Add(structReflectionData->GetStructCPPName(), testStruct);
//		}
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("Struct is NULL"));
//	}
//}

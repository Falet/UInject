#pragma once
#include "UInject/Bindings/BindUClassInject.h"
#include "UInject/Bindings/BindUInterfaceInject.h"
#include "UInject/Bindings/BindUStructInject.h"

#include "UDiContainer.generated.h"

UCLASS()
class UDiContainer : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UDiContainer* PreviousContainer;

	template <class T>
	BindUClassInject<T>* BindClass();
	template <class T>
	BindUInterfaceInject<T>* BindInterface();
	template <class T>
	BindUStructInject<T>* BindStruct();
	
	template <class T>
	BindUClassInject<T> BindUClass();
	template <class T>
	BindUInterfaceInject<T> BindUInterface();
	template <class T>
	BindUStructInject<T> BindUStruct();

	void** FindObjectInContainer(FProperty* fProperty);
	void** GetInjectObject(FProperty* fProperty);//move to up class
	bool CheckDuplicateInContainers(FString className);

	UFUNCTION(BlueprintCallable)
	void BindUClassFromBlueprint(UClass* classReflectionData, UObject* classObj);
	UFUNCTION(BlueprintCallable)
	void BindUInterfaceFromBlueprint(TSubclassOf<UInterface> interfaceUClass, UObject* interfaceObj);
	UFUNCTION(BlueprintCallable)
	void BindUFactoryFromBlueprint(TSubclassOf<UInjectFactory> factoryUClass, UInjectFactory* factoryObj = nullptr);

private:
	TMap<FString , void*> _container = TMap<FString , void*>();
	TSet<void*> _testC = TSet<void*>();
};

template <class T>
BindUClassInject<T>* UDiContainer::BindClass()
{
	
}

template <class T>
BindUInterfaceInject<T>* UDiContainer::BindInterface()
{
}

template <class T>
BindUStructInject<T>* UDiContainer::BindStruct()
{
}

template <class T>
BindUClassInject<T> UDiContainer::BindUClass()
{
	return BindUClassInject<T>(&_container);
}

template <class T>
BindUInterfaceInject<T> UDiContainer::BindUInterface()
{
	return BindUInterfaceInject<T>(&_container);
}

template <class T>
BindUStructInject<T> UDiContainer::BindUStruct()
{
	return BindUStructInject<T>(&_container);
}
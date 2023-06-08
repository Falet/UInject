#pragma once

template<class T, class R>
class BindFromUInterfaceInject final
{
public:
	explicit BindFromUInterfaceInject(TMap<FString , void*>* container)
	{
		_container = container;
	}
	void From(T* obj);
private:
	TMap<FString, void*>* _container;
};

template<class T, class R>
void BindFromUInterfaceInject<T, R>::From(T* obj)
{
	R* result = Cast<R>(obj);
	if (result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error type: Reference object isn't %s"), *R::StaticClass()->GetName());
		return;
	}
	
	auto classInterface = T::UClassType::StaticClass();
	
	TScriptInterface<T>* asd = new TScriptInterface<T>(result);
	_container->Add("<I" + classInterface->GetName() + ">", asd);
}



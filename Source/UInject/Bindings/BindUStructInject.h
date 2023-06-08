#pragma once

template<class T>
class BindUStructInject
{
public:
	explicit BindUStructInject(TMap<FString , void*>* container)
	{
		_container = container;
	}
	
	void From(T* obj);
private:
	TMap<FString , void*>* _container;
};

template <typename T>
void BindUStructInject<T>::From(T* objStruct)
{
	auto staticStruct =	T::StaticStruct();
	if (staticStruct)
	{
		
	}
		_container->Add(staticStruct->GetClass()->GetPrefixCPP() + staticStruct->GetName(), objStruct);
}
#pragma once
#include "BindFromUInterfaceInject.h"

template <typename T>
class BindUInterfaceInject final
{
public:
	explicit BindUInterfaceInject(TMap<FString , void*>* container)
	{
		_container = container;
	}
	template <class R>
	BindFromUInterfaceInject<T, R>* To();

private:
	TMap<FString, void*>* _container;
};

template <typename T>
template <typename R>
BindFromUInterfaceInject<T, R>* BindUInterfaceInject<T>::To()
{
	return new BindFromUInterfaceInject<T, R>(_container);
}





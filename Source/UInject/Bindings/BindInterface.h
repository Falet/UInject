#pragma once
#include "BindFromUInterfaceInject.h"

template <typename T>
class BindInterface final
{
public:
	explicit BindInterface(TMap<FString , void*>* container)
	{
		_container = container;
	}
	template <class R>
	BindFromUInterfaceInject<T, R> To();

private:
	TMap<FString, void*>* _container;
};

template <typename T>
template <typename R>
BindFromUInterfaceInject<T, R> BindInterface<T>::To()
{
	return BindFromUInterfaceInject<T, R>(_container);
}





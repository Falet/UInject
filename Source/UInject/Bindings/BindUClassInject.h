#pragma once

template<class T>
class BindUClassInject final
{
public:
	explicit BindUClassInject(TMap<FString , void*>* container)
	{
		_container = container;
	}
	
	void From(T* obj);

private:
	TMap<FString , void*>* _container;
};

template<>
class BindUClassInject<AActor*> final
{
public:
	explicit BindUClassInject(TMap<FString , void*>* container)
	{
		_container = container;
	}
	
	void From(AActor* obj)
	{
		auto staticClass = obj->StaticClass();
		char* pref1 = TCHAR_TO_ANSI(staticClass->GetPrefixCPP());
		char* pref2 = TCHAR_TO_ANSI(obj->GetClass()->GetPrefixCPP());
	
		if (pref1[0] != pref2[0])
		{
			_container->Add(staticClass->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
		}
		else
		{
			_container->Add(obj->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
		}
	}

private:
	TMap<FString , void*>* _container;
};

template <class T>
void BindUClassInject<T>::From(T* obj)
{
	auto staticClass = obj->StaticClass();
	char* pref1 = TCHAR_TO_ANSI(staticClass->GetPrefixCPP());
	char* pref2 = TCHAR_TO_ANSI(obj->GetClass()->GetPrefixCPP());
	
	if (pref1[0] != pref2[0])
	{
		_container->Add(staticClass->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
	}
	else
	{
		_container->Add(obj->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
	}
}

template<class T> 
struct RankOfArray 
{ static const int value = 0; };
// рекуррентный частично специализированный класс
template<class T, UClass* N> 
struct RankOfArray < T[N] > 
{ static const int value = 1+RankOfArray<T>::value; };

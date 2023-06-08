#pragma once

#define From(NameOfType, object) __InternalFrom( TEXT(#NameOfType), object)

class BindClass final
{
public:
	explicit BindClass(TMap<FString , void*>* container)
	{
		_container = container;
	}

	void __InternalFrom(T* obj);

private:
	TMap<FString , void*>* _container;
};

//template <class T>
//void BindClass<T>::From(T* obj)
//{
//	auto staticClass = obj->StaticClass();
//	char* pref1 = TCHAR_TO_ANSI(staticClass->GetPrefixCPP());
//	char* pref2 = TCHAR_TO_ANSI(obj->GetClass()->GetPrefixCPP());
//	
//	if (pref1[0] != pref2[0])
//	{
//		_container->Add(staticClass->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
//	}
//	else
//	{
//		_container->Add(obj->GetClass()->GetPrefixCPP() + staticClass->GetName() + "*", obj);
//	}
//}

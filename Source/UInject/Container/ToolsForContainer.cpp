#include "ToolsForContainer.h"
#include "UDiContainer.h"

void ToolsForContainer::Inject(const UClass* ReflectionClass, UDiContainer* container, UObject* obj)
{
	for (TFieldIterator<UFunction> PropIt(ReflectionClass); PropIt; ++PropIt)
	{
		UFunction* Function = *PropIt;
		
		if (Function->GetMetaData("Category") == "Injection")
		{
			FProperty* fProperty = Function->PropertyLink;
			uint8* Frame = (uint8*)FMemory_Alloca(Function->PropertiesSize);
			FOutParmRec* OutNew = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
			FOutParmRec* OutBegin = OutNew;
			int32 sizeobj = 0;
			while (fProperty)
			{
				if (!(fProperty->PropertyFlags & CPF_Parm))
				{
					break;
				}
				
				void** params = container->GetInjectObject(fProperty);
				if (params == NULL)
				{
					sizeobj = -1;
					break;
				}

				void* result;
				
				if (FObjectProperty* objProp = CastField<FObjectProperty>(fProperty))
				{
					result = params;
				}
				else
				{
					result = *params;
				}
				
				if (fProperty->PropertyFlags & CPF_OutParm)
				{
					OutNew->Property = fProperty;
					OutNew->PropAddr = (uint8*)result;
					FOutParmRec* OutNew1 = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
					OutNew->NextOutParm = OutNew1;
					OutNew = OutNew1;
				}
				
				if (result != NULL)
				{
					sizeobj += fProperty->GetOffset_ForInternal();
					FMemory::Memcpy(Frame + sizeobj, result, fProperty->ElementSize);
				}
				
				fProperty = fProperty->NextRef;
			}
			if (sizeobj != -1)
			{
				FFrame NewStack(obj, Function, Frame, NULL, Function->PropertyLink);
				NewStack.OutParms = OutBegin;
				if (!(Function->FunctionFlags & FUNC_Native))
				{
					Function->ProcessEvent(Function, Frame);
				}
				else
				{
					Function->Invoke(obj, NewStack, NULL);
				}
			}
		}
	}
}
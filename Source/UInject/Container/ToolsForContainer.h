#pragma once
#include "UDiContainer.h"

class ToolsForContainer
{
public:
	static void Inject(const UClass* component, UDiContainer* container, UObject* obj);
};

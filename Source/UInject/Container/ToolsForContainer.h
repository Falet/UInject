#pragma once

class UDiContainer;

class ToolsForContainer
{
public:
	static void Inject(const UClass* component, UDiContainer* container, UObject* obj);
};

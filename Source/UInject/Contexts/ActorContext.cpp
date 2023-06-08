// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorContext.h"
#include "SceneContext.h"
#include "Engine/SCS_Node.h"
#include "UInject/TestInstaller.h"
#include "UInject/Container/ToolsForContainer.h"
#include "UInject/Container/UDiContainer.h"

UActorContext::UActorContext()
{
	bWantsInitializeComponent = true;
}

void UActorContext::OnRegister()
{
	Super::OnRegister();
}

void UActorContext::OnUnregister()
{
	Super::OnUnregister();
}

void UActorContext::InitializeComponent()
{
	Super::InitializeComponent();
}

void UActorContext::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UActorContext::RegisterBindings(UDiContainer* worldContainer)
{
	_container = NewObject<UDiContainer>();
	_container->PreviousContainer = worldContainer;
	for(int i = 0; i < _installersTest.Num(); i++)
	{
		UClass* get = _installersTest[i].Get();
		auto testComp = NewObject<UInstaller>(GetOwner(), get, _installersTest[i]->GetFName());
		testComp->InstallBindingsInCPP(_container);
		testComp->InstallBindingsInBlueprint(_container);
		testComp->DestroyComponent();
	}
}

void UActorContext::RegisterChild(UActorContext* child)
{
	child->RegisterBindings(_container);
	child->Injection();
}

UActorComponent*  UActorContext::FindDefaultComponentByClass(const TSubclassOf<AActor> InActorClass,
                                                             const TSubclassOf<UActorComponent> InComponentClass)
{
	if (!IsValid(InActorClass))
	{
		return nullptr;
	}

	// Check CDO.
	AActor* ActorCDO = InActorClass->GetDefaultObject<AActor>();
	UActorComponent* FoundComponent = ActorCDO->FindComponentByClass(InComponentClass);

	if (FoundComponent != nullptr)
	{
		return FoundComponent;
	}

	// Check blueprint nodes. Components added in blueprint editor only (and not in code) are not available from
	// CDO.
	UBlueprintGeneratedClass* RootBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(InActorClass);
	UClass* ActorClass = InActorClass;

	// Go down the inheritance tree to find nodes that were added to parent blueprints of our blueprint graph.
	do
	{
		UBlueprintGeneratedClass* ActorBlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(ActorClass);
		if (!ActorBlueprintGeneratedClass)
		{
			return nullptr;
		}

		const TArray<USCS_Node*>& ActorBlueprintNodes =
			ActorBlueprintGeneratedClass->SimpleConstructionScript->GetAllNodes();
		
		for (USCS_Node* Node : ActorBlueprintNodes)
		{
			if (Node->ComponentClass->IsChildOf(InComponentClass))
			{
				return Node->GetActualComponentTemplate(RootBlueprintGeneratedClass);
			}
		}

		ActorClass = Cast<UClass>(ActorClass->GetSuperStruct());

	} while (ActorClass != AActor::StaticClass());

	return nullptr;
}

void UActorContext::Injection()
{
	ToolsForContainer::Inject(GetOwner()->GetClass(), _container, GetOwner());
	
	TArray<UActorComponent*> tempComponent;
	GetOwner()->GetComponents(tempComponent);
	for(UActorComponent* component : tempComponent)
	{
		ToolsForContainer::Inject(component->GetClass(), _container, component);
	}
}


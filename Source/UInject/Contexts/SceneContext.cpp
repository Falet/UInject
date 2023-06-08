// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneContext.h"

#include "UInject/Installer.h"
#include "ActorContext.h"
#include "Kismet/GameplayStatics.h"
#include "UInject/Container/ToolsForContainer.h"
#include "UInject/Container/UDiContainer.h"
#include "UInject/Factory/ActorInjection.h"

void ASceneContext::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASceneContext::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	UE_LOG(LogTemp, Error, TEXT("1"));
}

void ASceneContext::PostLoad()
{
	Super::PostLoad();
	UE_LOG(LogTemp, Error, TEXT("2"));
}

void ASceneContext::PostActorCreated()
{
	Super::PostActorCreated();
	UE_LOG(LogTemp, Error, TEXT("3"));
}

ASceneContext::ASceneContext()
{
	ActorOnConstructionDelegate = FOnActorInjectionSpawned::FDelegate::CreateUObject(this, &ASceneContext::OnConstructionActor);
}

void ASceneContext::RegisterBinding()
{
	_installers = TArray<UInstaller*>();
	GetComponents<UInstaller>(_installers);
	for (int i = 0; i < _installers.Num(); i++)
	{
		_installers[i]->InstallBindingsInCPP(_container);
		_installers[i]->InstallBindingsInBlueprint(_container);
	}
}

void ASceneContext::RegisterWorldBindings(TArray<UActorContext*>& actorsForInjection)
{
	TArray<AActor*> tempFoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), tempFoundActors);

	for (AActor* actor : tempFoundActors)
	{
		if (UActorContext* context = GetActorContext(actor))
		{
			context->RegisterBindings(_container);
			actorsForInjection.Add(context);
		}
	}
}

void ASceneContext::Injection(TArray<UActorContext*>& actorsForInjection)
{
	ToolsForContainer::Inject(GetClass(), _container, this);
	
	for (UActorContext* actorContext : actorsForInjection)
	{
		actorContext->Injection();
	}
}

void ASceneContext::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ASceneContext::PrimaryInitializeComponents()
{
	_container = NewObject<UDiContainer>();
	RegisterBinding();

	TArray<UActorContext*> actorsForInjection;
	RegisterWorldBindings(actorsForInjection);

	Injection(actorsForInjection);
}

UActorContext* ASceneContext::GetActorContext(AActor* InActor)
{
	TArray<UActorContext*> components;
	InActor->GetComponents<UActorContext>(components);
	if (components.Num() > 1)
	{
		//Error
		return nullptr;
	}
	
	if (components.Num() == 1)
	{
		return components[0];
	}
	
	return nullptr;
}

void ASceneContext::RegisterActor(AActor* InActor)
{
	if (InActor->IsChildActor())
	{
		AActor* parentActor = InActor->GetOwner();
		if (parentActor)
		{
			UActorContext* context = GetActorContext(parentActor);
			UActorContext* contextChild = GetActorContext(InActor);
			if (context && contextChild)
			{
				context->RegisterChild(contextChild);
				return;
			}
		}
	}
	
	if (UActorContext* context = GetActorContext(InActor))
	{
		context->RegisterBindings(_container);
		context->Injection();
	}
}

void ASceneContext::OnConstructionActor(AActorInjection* InActor)
{
	RegisterActor(InActor);
	//InActor->TriggeredOnConstruction.Remove(ActorOnConstructionDelegate.GetHandle());
	InActor->TriggeredOnConstruction.Remove(ActorOnConstructionDelegate.GetHandle());
}

void ASceneContext::PreInitializeActor(AActor* InActor)
{
	if (!InActor)
	{
		return;
	}
	
	if (AActorInjection* actorInjection = Cast<AActorInjection>(InActor))
	{
		//actorInjection->GetEvent().Broadcast(actorInjection);
		//actorInjection->TriggeredOnConstruction.Add(ActorOnConstructionDelegate);
		actorInjection->TriggeredOnConstruction.Add(ActorOnConstructionDelegate);
	}
	
	RegisterActor(InActor);
}





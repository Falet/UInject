// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "Contexts/ActorContext.h"
#include "GameFramework/Actor.h"
#include "TestAll/InterfaceInheritanceChild1.h"
#include "InjectTarget.generated.h"

UCLASS()
class UINJECT_API AInjectTarget : public AActor
{
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PreInitializeComponents() override;
private:
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AInjectTarget();
	
	template<typename T>
	UFUNCTION(BlueprintCallable)
	void Func123(T* df);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostRegisterAllComponents() override;

	UFUNCTION(Category=Injection)
	void TestInjectionCpp(TScriptInterface<IMyInterface> inter);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
	USceneComponent* SceneComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Custom")
	UActorContext* ActorContext;
};

template <typename T>
void AInjectTarget::Func123(T* df)
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectInfo.h"

#include "InteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_TEST_5_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractorComponent();

	bool InteractWith(UObjectInfo* info);

	bool PickUp();

	// Can the object be interacted with ?
	UPROPERTY(VisibleAnywhere)
		bool bIsInteractable;

	// Can the object be picked ?
	UPROPERTY(VisibleAnywhere)
		bool bIsPickable;

protected:
	virtual bool Interact(UObjectInfo* info);

		
};

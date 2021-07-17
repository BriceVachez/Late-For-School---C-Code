// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectInfo.h"
#include "InteractableActor.h"

#include "PlayerInteractorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_TEST_5_API UPlayerInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractorComponent();

	bool Interact(UObjectInfo* info);

	UPROPERTY(EditAnywhere)
		float MaxInteractionDistance = 100.0f;

	AInteractableActor* PickUp();

	AInteractableActor* FindClosestInteractableActorWithRayTrace();

		
};

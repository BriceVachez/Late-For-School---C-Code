// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"
#include "InteractableActor.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}



bool UInteractorComponent::Interact(UObjectInfo* info)
{
	// You have to ovrride from this
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You must override from this class"));
	}
	return false;
}

bool UInteractorComponent::InteractWith(UObjectInfo* info)
{
	if (bIsInteractable) {
		return Interact(info);
	}
	// Add something to say we can't interact (like a sound)
	return false;
}

bool UInteractorComponent::PickUp()
{
	if (bIsPickable) {
		AInteractableActor* owner = Cast<AInteractableActor>(GetOwner());
		if (owner->Info->ObjectId.Contains("key")) {
			owner->PlaySound("pickup", owner->GetActorLocation());
		}
		return true;
	}
	// Add something to say we can't pickup (like a sound)

	return false;
}

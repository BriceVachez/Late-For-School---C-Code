// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractorComponent.h"
#include "Door1.h"

bool UDoorInteractorComponent::Interact(UObjectInfo* info) {
	ADoor1* owner = (ADoor1*)GetOwner();
	if (owner) {
		if (owner->IsLocked) {
			owner->PlaySound("locked", owner->GetActorLocation());
			return false;
		}
		else {
			owner->FindComponentByClass<UActionComponent>()->DoAction();
			return true;
		}
	}
	return false;
}


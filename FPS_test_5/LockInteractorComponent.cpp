// Fill out your copyright notice in the Description page of Project Settings.


#include "LockInteractorComponent.h"
#include "ActionComponent.h"
#include "Lock1.h"

bool ULockInteractorComponent::Interact(UObjectInfo* info) {
	if(GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tried to activate lock."));
	}
	if (KeyId.Equals(info->ObjectId)) {
		GetOwner()->FindComponentByClass<UActionComponent>()->DoAction();
		return true;
	}
	else {
		Cast<ALock1>(GetOwner())->PlaySound("locked", GetOwner()->GetActorLocation());
		return false;
	}
}


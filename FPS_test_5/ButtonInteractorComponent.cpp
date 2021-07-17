// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonInteractorComponent.h"
#include "ActionComponent.h"

bool UButtonInteractorComponent::Interact(UObjectInfo* info) {
	GetOwner()->FindComponentByClass<UActionComponent>()->DoAction();
	return true;
}


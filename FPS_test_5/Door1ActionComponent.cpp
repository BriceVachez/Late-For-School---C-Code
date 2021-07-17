// Fill out your copyright notice in the Description page of Project Settings.


#include "Door1ActionComponent.h"
#include "Door1.h"

void UDoor1ActionComponent::DoAction() {
    ADoor1* owner = (ADoor1*)GetOwner();
    if (owner) {
        owner->ChangeState();
    }
}


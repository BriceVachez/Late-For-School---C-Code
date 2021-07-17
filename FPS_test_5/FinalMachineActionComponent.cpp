// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalMachineActionComponent.h"
#include "FinalMachine.h"

void UFinalMachineActionComponent::DoAction() {
	AFinalMachine* owner = Cast<AFinalMachine>(GetOwner());
	if (owner) {
		int code = owner->GetCompleteCode();
		if (code == trueEndingCode) {
			owner->PlaySound("ok", owner->GetActorLocation());
			owner->PlayEndAnimation(true);
		}
		else {
			owner->PlaySound("boom", owner->GetActorLocation());
			owner->PlayEndAnimation(false);
		}
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalMachineInteractorComponent.h"
#include "FinalMachine.h"
#include "FPS_test_5Character.h"

bool UFinalMachineInteractorComponent::Interact(UObjectInfo* info) {
	int flaskUsed = 0;
	if (FirstFlaskId.Equals(info->ObjectId)) {
		flaskUsed = 1;
	}
	else if (SecondFlaskId.Equals(info->ObjectId)) {
		flaskUsed = 2;
	}
	else if (ThirdFlaskId.Equals(info->ObjectId)) {
		flaskUsed = 3;
	}
	if (flaskUsed != 0) {
		AFPS_test_5Character* player = (AFPS_test_5Character*)GetWorld()->GetFirstPlayerController()->GetPawn();
		if (player) {
			AFinalMachine* owner = Cast<AFinalMachine>(GetOwner());
			if (owner) {
				owner->NotifyFlaskUsed(flaskUsed, info);
				player->UnequipCurrentItem();
				return true;
			}
		}
	}
	return false;
}
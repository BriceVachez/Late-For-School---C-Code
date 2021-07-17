// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock1ActionComponent.h"
#include "Lock1.h"
#include "FPS_test_5Character.h"

void ULock1ActionComponent::DoAction() {
	ALock1* owner = (ALock1*)GetOwner();
	if (owner->Door != nullptr) {
		owner->Door->Unlock();
	}
	AFPS_test_5Character* player = (AFPS_test_5Character*)GetWorld()->GetFirstPlayerController()->GetPawn();
	player->UnequipCurrentItem();
	GetOwner()->Destroy();
}


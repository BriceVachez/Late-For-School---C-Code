// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerActionComponent.h"
#include "FPS_test_5Character.h"
#include "Locker1.h"

void ULockerActionComponent::DoAction() {
	if (GetOwner()->GetWorld()) {
		AFPS_test_5Character* player = (AFPS_test_5Character*)GetOwner()->GetWorld()->GetFirstPlayerController()->GetPawn();
		ALocker1* owner = Cast<ALocker1>(GetOwner());
		if (owner) {
			owner->PlaySound("opening", owner->GetActorLocation());
		}
		player->FullyOpenInventory();
	}
}


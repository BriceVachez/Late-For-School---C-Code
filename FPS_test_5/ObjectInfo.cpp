// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectInfo.h"
#include "FPS_test_5Character.h"

// Sets default values for this component's properties
UObjectInfo::UObjectInfo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Player = nullptr;

	// ...
}


// Override from this to override RMB action
void UObjectInfo::UtilityFunction()
{
	if (Player != nullptr) {
		Cast<AFPS_test_5Character>(Player)->Interact();
	}
}


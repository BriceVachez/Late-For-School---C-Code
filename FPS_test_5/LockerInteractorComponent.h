// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractorComponent.h"
#include "LockerInteractorComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ULockerInteractorComponent : public UInteractorComponent
{
	GENERATED_BODY()

protected:
	bool Interact(UObjectInfo* info) override;
	
};

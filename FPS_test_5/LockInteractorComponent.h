// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractorComponent.h"
#include "LockInteractorComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ULockInteractorComponent : public UInteractorComponent
{
	GENERATED_BODY()


public:
	// ID of the key neededg
	UPROPERTY(EditAnywhere)
		FString KeyId;

protected:
	bool Interact(UObjectInfo* info) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractorComponent.h"
#include "FinalMachineInteractorComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API UFinalMachineInteractorComponent : public UInteractorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FString FirstFlaskId;

	UPROPERTY(EditAnywhere)
		FString SecondFlaskId;

	UPROPERTY(EditAnywhere)
		FString ThirdFlaskId;

protected:
	bool Interact(UObjectInfo* info) override;
	
};

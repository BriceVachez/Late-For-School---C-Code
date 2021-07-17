// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectInfo.h"
#include "Trap1Info.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API UTrap1Info : public UObjectInfo
{
	GENERATED_BODY()

public:

	UTrap1Info();

	void UtilityFunction() override;

	UPROPERTY(EditAnywhere)
		float TrapPlacementDistance = 250.0f;

private:

	FHitResult FindWherePlayerIsLooking();
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectInfo.h"
#include "Key1Info.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API UKey1Info : public UObjectInfo
{
	GENERATED_BODY()

public:

	UKey1Info();

	void UtilityFunction() override;
	
};

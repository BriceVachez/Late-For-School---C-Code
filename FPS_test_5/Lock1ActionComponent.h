// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionComponent.h"
#include "Lock1ActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ULock1ActionComponent : public UActionComponent
{
	GENERATED_BODY()

public:
	void DoAction() override;

	
};

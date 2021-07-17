// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionComponent.h"
#include "LockerActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ULockerActionComponent : public UActionComponent
{
	GENERATED_BODY()

public:
	void DoAction() override;
	
};

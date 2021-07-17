// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionComponent.h"
#include "Door1ActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API UDoor1ActionComponent : public UActionComponent
{
	GENERATED_BODY()

public:
	void DoAction() override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Trap1.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ATrap1 : public AInteractableActor
{
	GENERATED_BODY()

public:

	ATrap1();

protected:

	virtual void BeginPlay() override;

	void LoadMesh() override;
	
};

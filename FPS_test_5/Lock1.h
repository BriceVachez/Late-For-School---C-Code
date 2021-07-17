// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Door1.h"
#include "Sound/SoundWave.h"

#include "Lock1.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ALock1 : public AInteractableActor
{
	GENERATED_BODY()

public:

	ALock1();

	UPROPERTY(EditAnywhere)
		ADoor1* Door;

	UPROPERTY(EditAnywhere)
		USoundWave* LockedDoor;

	virtual void PlaySound(FString soundName, FVector location) override;
};

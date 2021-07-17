// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Sound/SoundWave.h"
#include "Key1.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API AKey1 : public AInteractableActor
{
	GENERATED_BODY()
public:
	AKey1();
	
	virtual void PlaySound(FString soundName, FVector location) override;

protected:
	UPROPERTY(EditAnywhere)
		USoundWave* PickUpSound;
};

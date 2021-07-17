// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Sound/SoundWave.h"
#include "FinalMachine.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API AFinalMachine : public AInteractableActor
{
	GENERATED_BODY()

public:

	AFinalMachine();
	void LoadMesh() override;

	void NotifyFlaskUsed(int flaskNumber, UObjectInfo* flaskInfo);

	int GetCompleteCode();


	UFUNCTION(BlueprintNativeEvent)
		void PlayEndAnimation(bool isTrueEnding);
	virtual void PlayEndAnimation_Implementation(bool isTrueEnding);

	void PlaceFlask(FString flaskMesh);

	virtual void PlaySound(FString soundName, FVector location) override;

	UPROPERTY(EditAnywhere)
		FString EndSoundWaveName = "";

	UFUNCTION(BlueprintNativeEvent)
		void PlayEndSound();
	void PlayEndSound_Implementation();

private:

	//Sounds
	UPROPERTY(EditAnywhere)
		USoundWave* SoundOK;

	UPROPERTY(EditAnywhere)
		USoundWave* SoundBoom;

	UPROPERTY(VisibleAnywhere)
		int flasksUsedCounter;

	UPROPERTY(VisibleAnywhere)
		int flasksUsedCode;

	UPROPERTY(EditAnywhere)
		UAnimSequence* EndAnimation;

	UPROPERTY(EditAnywhere)
		FVector OffsetFlask1;

	UPROPERTY(EditAnywhere)
		FVector OffsetFlask2;

	UPROPERTY(EditAnywhere)
		FVector OffsetFlask3;

	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> Flasks;



	
};

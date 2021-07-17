// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Sound/SoundWave.h"
#include "Door1.generated.h"

/**
 *
 */
UCLASS()
class FPS_TEST_5_API ADoor1 : public AInteractableActor
{
	GENERATED_BODY()


public:

	ADoor1();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LoadMesh() override;

	UPROPERTY(EditAnywhere)
		bool IsLocked;

	UPROPERTY(EditAnywhere)
		bool IsOpen;

	UPROPERTY(EditAnywhere)
		bool IsClosed;

	UPROPERTY(EditAnywhere)
		float OpeningDuration;

	UPROPERTY(EditAnywhere)
		float ClosingDuration;

	UPROPERTY(EditAnywhere)
		float OpenAngle;

	UPROPERTY(EditAnywhere)
		float ClosedAngle;

	void Unlock();

	void ChangeState();

	virtual void PlaySound(FString soundName, FVector location) override;


private:

	UPROPERTY(VisibleAnywhere)
		bool IsOpening;

	UPROPERTY(VisibleAnywhere)
		bool IsClosing;

	UPROPERTY(VisibleAnywhere)
		float ActualAngle;

	UPROPERTY(EditAnywhere)
		float OffsetX = -1.0f;
	UPROPERTY(EditAnywhere)
		float OffsetY = -1.0f;
	UPROPERTY(EditAnywhere)
		float OffsetZ = -1.0f;

	void SetOpen();
	void SetClosed();

protected:
	virtual void BeginPlay() override;

	// SOunds
	UPROPERTY(EditAnywhere)
		USoundWave* LockedDoor;

	UPROPERTY(EditAnywhere)
		USoundWave* OpeningDoor;

	UPROPERTY(EditAnywhere)
		USoundWave* ClosingDoor;

	UPROPERTY(EditAnywhere)
		USoundWave* UnlockedDoor;

};

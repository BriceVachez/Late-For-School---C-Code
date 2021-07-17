// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Sound/SoundWave.h"
#include "Locker1.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API ALocker1 : public AInteractableActor
{
	GENERATED_BODY()

public:

	ALocker1();

	UPROPERTY(VisibleAnywhere)
		TArray<UObjectInfo*> Storage;

	UObjectInfo* PickupItem(int itemPosX, int itemPosY);

	void AddItem(UObjectInfo* itemAdded, int itemPosX, int itemPosY);

	virtual void PlaySound(FString soundName, FVector location) override;

	UPROPERTY(EditAnywhere)
		int StorageSizeX;

	UPROPERTY(EditAnywhere)
		int StorageSizeY;

private:

	void InitializeStorage();

	void InitOnPlay();

	UPROPERTY(EditAnywhere)
		USoundWave* OpeningLocker;

	UPROPERTY(EditAnywhere)
		USoundWave* ClosingLocker;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

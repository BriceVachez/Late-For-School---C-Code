// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock1.h"
#include "LockInteractorComponent.h"
#include "Lock1ActionComponent.h"
#include "Kismet/GameplayStatics.h"

ALock1::ALock1() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	ULockInteractorComponent* lockInteractionComponent = CreateDefaultSubobject<ULockInteractorComponent>(TEXT("Lock Interactor Component"));
	lockInteractionComponent->KeyId = "key1";
	InteractorComponent = lockInteractionComponent;
	InteractorComponent->bIsPickable = false;
	InteractorComponent->bIsInteractable = true;

	ActionComponent = CreateDefaultSubobject<ULock1ActionComponent>(TEXT("Lock 1 Action Component"));

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Object Infos"));
	Info->Name = "Lock 1";
	Info->ObjectId = "lock1";
	Info->Description = "First lock";
	Info->MeshReference = "/Game/Asset/Sphere/Sphere_1.Sphere";
	Info->ImageReference = "none";

	static ConstructorHelpers::FObjectFinder<USoundWave> lockedDoorWave(
		TEXT("SoundWave'/Game/Asset/Sounds/door_locked.door_locked'")
	);
	LockedDoor = lockedDoorWave.Object;
}

void ALock1::PlaySound(FString soundName, FVector location) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *soundName);
	}
	if (soundName.Equals("locked")) {
		UGameplayStatics::PlaySound2D(GetWorld(), LockedDoor);
	}
}

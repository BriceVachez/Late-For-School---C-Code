// Fill out your copyright notice in the Description page of Project Settings.


#include "Key1.h"
#include "Kismet/GameplayStatics.h"

AKey1::AKey1() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor Component"));
	InteractorComponent->bIsPickable = true;
	InteractorComponent->bIsInteractable = false;

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("Action Component"));

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Object Infos"));

	static ConstructorHelpers::FObjectFinder<USoundWave> pickUpSoundWave(
		TEXT("SoundWave'/Game/Asset/Sounds/key_pickup.key_pickup'")
	);

	PickUpSound = pickUpSoundWave.Object;
}

void AKey1::PlaySound(FString soundName, FVector location) {
	if (soundName.Equals("pickup")) {
		UGameplayStatics::PlaySound2D(GetWorld(), PickUpSound);
	}
}


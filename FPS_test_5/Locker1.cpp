// Fill out your copyright notice in the Description page of Project Settings.


#include "Locker1.h"
#include "ButtonInteractorComponent.h"
#include "LockerActionComponent.h"
#include "Kismet/GameplayStatics.h"

ALocker1::ALocker1() {
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InteractorComponent = CreateDefaultSubobject<UButtonInteractorComponent>(TEXT("Interactor Component"));
	InteractorComponent->bIsPickable = false;
	InteractorComponent->bIsInteractable = true;

	ActionComponent = CreateDefaultSubobject<ULockerActionComponent>(TEXT("Action Component"));

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Object Infos"));
	Info->Name = "Locker1";
	Info->ObjectId = "locker1";
	Info->Description = "";
	Info->MeshReference = "placeholder";
	Info->ImageReference = "";

	StorageSizeX = 9;
	StorageSizeY = 5;
	InitializeStorage();

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	static ConstructorHelpers::FObjectFinder<USoundWave> openingLockerWave(
		TEXT("SoundWave'/Game/Asset/Sounds/locker_open.locker_open'")
	);
	OpeningLocker = openingLockerWave.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> closingLockerWave(
		TEXT("SoundWave'/Game/Asset/Sounds/locker_close.locker_close'")
	);
	ClosingLocker = closingLockerWave.Object;
}

void ALocker1::BeginPlay() {
	Super::BeginPlay();
	InitOnPlay();
}

void ALocker1::InitOnPlay() {
	Storage.Empty();
	UObjectInfo* noneObject;
	noneObject = NewObject<UObjectInfo>(UObjectInfo::StaticClass(), TEXT("None Object"));
	noneObject->Name = "noneObject";
	noneObject->Description = "none";
	noneObject->ObjectId = "none";
	noneObject->MeshReference = "none";
	noneObject->ImageReference = "/Game/Asset/Images/none.Texture2D_0";

	for (int i = 0; i < StorageSizeX * StorageSizeY; ++i) {
		Storage.Add(noneObject);
	}
}

void ALocker1::InitializeStorage() {
	UObjectInfo* noneObject = CreateDefaultSubobject<UObjectInfo>(TEXT("Info"));
	noneObject->Name = "noneObject";
	noneObject->Description = "none";
	noneObject->ObjectId = "none";
	noneObject->MeshReference = "none";
	noneObject->ImageReference = "/Game/Asset/Images/none.Texture2D_0";

	for (int i = 0; i < StorageSizeX * StorageSizeY; ++i) {
		Storage.Add(noneObject);
	}
}

UObjectInfo* ALocker1::PickupItem(int itemPosX, int itemPosY) {
	//UObjectInfo* object = Storage[itemPosX + itemPosY * StorageSizeX];
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Name : %s"), *Storage[itemPosX + itemPosY * StorageSizeX]->Name));
	//}
	if (Storage[itemPosX + itemPosY * StorageSizeX] == nullptr) {
		UObjectInfo* noneObject = NewObject<UObjectInfo>(UObjectInfo::StaticClass(), TEXT("None Object"));
		noneObject->Name = "noneObject";
		noneObject->Description = "none";
		noneObject->ObjectId = "none";
		noneObject->MeshReference = "none";
		noneObject->ImageReference = "/Game/Asset/Images/none.Texture2D_0";
		return noneObject;
	}
	else {
		return Storage[itemPosX + itemPosY * StorageSizeX];
	}
}

void ALocker1::AddItem(UObjectInfo* itemAdded, int itemPosX, int itemPosY) {
	Storage[itemPosX + itemPosY * StorageSizeX] = itemAdded;
}

void ALocker1::PlaySound(FString soundName, FVector location) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *soundName);
	}
	if (soundName.Equals("opening")) {
		UGameplayStatics::PlaySound2D(GetWorld(), OpeningLocker);
	}
	else if (soundName.Equals("closing")) {
		UGameplayStatics::PlaySound2D(GetWorld(), ClosingLocker);
	}
}


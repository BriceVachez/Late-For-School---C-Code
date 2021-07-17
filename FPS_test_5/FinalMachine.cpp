// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalMachine.h"
#include "FinalMachineInteractorComponent.h"
#include "FinalMachineActionComponent.h"
#include "Key1.h"
#include "Kismet/GameplayStatics.h"

AFinalMachine::AFinalMachine() {
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	UFinalMachineInteractorComponent* finalMachineInteractorComponent =
		CreateDefaultSubobject<UFinalMachineInteractorComponent>(TEXT("Final Machine Interactor Component"));
	finalMachineInteractorComponent->FirstFlaskId = "flask1";
	finalMachineInteractorComponent->SecondFlaskId = "flask2";
	finalMachineInteractorComponent->ThirdFlaskId = "flask3";
	InteractorComponent = finalMachineInteractorComponent;
	InteractorComponent->bIsPickable = false;
	InteractorComponent->bIsInteractable = true;

	UFinalMachineActionComponent* finalMachineActionComponent =
		CreateDefaultSubobject<UFinalMachineActionComponent>(TEXT("Final Machine Action Component"));
	finalMachineActionComponent->trueEndingCode = 231;
	ActionComponent = finalMachineActionComponent;

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Final Machine Infos"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	static ConstructorHelpers::FObjectFinder<USoundWave> soundOKWave(
		TEXT("SoundWave'/Game/Asset/Sounds/chemistry-ok.chemistry-ok'")
	);
	SoundOK = soundOKWave.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> soundBoomWave(
		TEXT("SoundWave'/Game/Asset/Sounds/chemistry_boom1.chemistry_boom1'")
	);
	SoundBoom = soundBoomWave.Object;
}

void AFinalMachine::NotifyFlaskUsed(int flaskNumber, UObjectInfo* flaskInfo) {
	flasksUsedCode += FMath::Pow(10, flasksUsedCounter) * flaskNumber;
	PlaceFlask(flaskInfo->MeshReference);
	if (flasksUsedCounter == 2) {
		ActionComponent->DoAction();
	}
	flasksUsedCounter++;
}

int AFinalMachine::GetCompleteCode() {
	return flasksUsedCode;
}

void AFinalMachine::LoadMesh() {}

void AFinalMachine::PlayEndAnimation_Implementation(bool isTrueEnding) {
	USkeletalMeshComponent* machineMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (machineMesh && EndAnimation) {
		machineMesh->PlayAnimation(EndAnimation, false);
	}

	for (int i = 0; i < Flasks.Num(); ++i) {
		Flasks[i]->Destroy();
	}
}

void AFinalMachine::PlaceFlask(FString flaskMesh) {
	FVector offset = FVector();
	switch (flasksUsedCounter) {
	case 0:
		offset = OffsetFlask1;
		break;
	case 1:
		offset = OffsetFlask2;
		break;
	case 2:
		offset = OffsetFlask3;
		break;
	default:
		return;
	}
	if (GetWorld()) {
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		AKey1* flask = GetWorld()->SpawnActor<AKey1>(GetActorLocation() + offset, Rotation, SpawnInfo);
		flask->Info->MeshReference = flaskMesh;
		flask->InteractorComponent->bIsPickable = false;
		flask->LoadMesh();
		Flasks.Add(flask);
	}
}

void AFinalMachine::PlaySound(FString soundName, FVector location) {
	EndSoundWaveName = soundName;
}

void AFinalMachine::PlayEndSound_Implementation() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *EndSoundWaveName);
	}
	if (EndSoundWaveName.Equals("ok")) {
		UGameplayStatics::PlaySound2D(GetWorld(), SoundOK);
	}
	else if (EndSoundWaveName.Equals("boom")) {
		UGameplayStatics::PlaySound2D(GetWorld(), SoundBoom);
	}
}

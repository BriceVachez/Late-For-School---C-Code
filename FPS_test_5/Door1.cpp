// Fill out your copyright notice in the Description page of Project Settings.


#include "Door1.h"
#include "Door1ActionComponent.h"
#include "DoorInteractorComponent.h"
#include "Kismet/GameplayStatics.h"


ADoor1::ADoor1() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InteractorComponent = CreateDefaultSubobject<UDoorInteractorComponent>(TEXT("Door Interactor Component"));
	InteractorComponent->bIsPickable = false;
	InteractorComponent->bIsInteractable = true;

	ActionComponent = CreateDefaultSubobject<UDoor1ActionComponent>(TEXT("Door 1 Action Component"));

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Object Infos"));
	Info->Name = "Door 1";
	Info->ObjectId = "door1";
	Info->Description = "First door";
	Info->MeshReference = "/Game/Asset/Sphere/Sphere_1.Sphere";
	Info->ImageReference = "none";

	ClosingDuration = 2.0f;
	OpeningDuration = 1.0f;

	ClosedAngle = 0.0f;
	OpenAngle = 90.0f;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	static ConstructorHelpers::FObjectFinder<USoundWave> lockedDoorWave(
		TEXT("SoundWave'/Game/Asset/Sounds/door_locked.door_locked'")
	);
	LockedDoor = lockedDoorWave.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> openingDoorWave(
		TEXT("SoundWave'/Game/Asset/Sounds/door_open.door_open'")
	);
	OpeningDoor = openingDoorWave.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> closingDoorWave(
		TEXT("SoundWave'/Game/Asset/Sounds/door_close.door_close'")
	);
	ClosingDoor = closingDoorWave.Object;
	static ConstructorHelpers::FObjectFinder<USoundWave> unlockedDoorWave(
		TEXT("SoundWave'/Game/Asset/Sounds/door_unlock.door_unlock'")
	);
	UnlockedDoor = unlockedDoorWave.Object;

}

// Called when the game starts or when spawned
void ADoor1::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor1::LoadMesh() {
	Super::LoadMesh();
	MeshComponent->SetRelativeScale3D(FVector(1, 1, 1));
	if (OffsetX == -1.0f) {
		OffsetX = MeshComponent->Bounds.BoxExtent.X;
	}
	if (OffsetY == -1.0f) {
		OffsetY = MeshComponent->Bounds.BoxExtent.Y;
	}
	if (OffsetY == -1.0f) {
		OffsetZ = MeshComponent->Bounds.BoxExtent.Z;
	}
	MeshComponent->SetRelativeLocation(FVector(OffsetX, OffsetY, OffsetZ));
}

void ADoor1::Tick(float DeltaTime) {
	if (IsOpening) {
		float deltaAngle = (OpenAngle - ClosedAngle) * DeltaTime / OpeningDuration;
		FRotator actorRotation = GetActorRotation();
		actorRotation.Yaw += deltaAngle;
		ActualAngle += deltaAngle;
		SetActorRotation(actorRotation);
		if (ActualAngle >= OpenAngle) {
			SetOpen();
		}
	}
	else if (IsClosing) {
		float deltaAngle = (ClosedAngle - OpenAngle) * DeltaTime / ClosingDuration;
		FRotator actorRotation = GetActorRotation();
		actorRotation.Yaw += deltaAngle;
		ActualAngle += deltaAngle;
		SetActorRotation(actorRotation);
		if (ActualAngle <= ClosedAngle) {
			SetClosed();
		}

	}
}

void ADoor1::ChangeState() {
	if (IsOpen || IsOpening) {
		IsOpening = false;
		IsClosing = true;
		IsOpen = false;
	}
	else {
		PlaySound("opening", GetActorLocation());
		IsOpening = true;
		IsClosing = false;
		IsClosed = false;
	}
}

void ADoor1::Unlock() {
	IsLocked = false;
	PlaySound("unlocked", GetActorLocation());
}

void ADoor1::SetOpen() {
	IsOpening = false;
	IsOpen = true;
	FRotator actorRotation = GetActorRotation();
	actorRotation.Yaw -= ActualAngle - OpenAngle;
	SetActorRotation(actorRotation);
	ActualAngle = OpenAngle;
}

void ADoor1::SetClosed() {
	PlaySound("closing", GetActorLocation());
	IsClosing = false;
	IsClosed = true;
	FRotator actorRotation = GetActorRotation();
	actorRotation.Yaw -= ActualAngle - ClosedAngle;
	SetActorRotation(actorRotation);
	ActualAngle = ClosedAngle;
}

void ADoor1::PlaySound(FString soundName, FVector location) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *soundName);
	}
	if (soundName.Equals("unlocked")) {
		UGameplayStatics::PlaySound2D(GetWorld(), UnlockedDoor);
	}
	else if (soundName.Equals("locked")) {
		UGameplayStatics::PlaySound2D(GetWorld(), LockedDoor);
	}
	else if (soundName.Equals("opening")) {
		UGameplayStatics::PlaySound2D(GetWorld(), OpeningDoor);
	}
	else if (soundName.Equals("closing")) {
		UGameplayStatics::PlaySound2D(GetWorld(), ClosingDoor);
	}
}

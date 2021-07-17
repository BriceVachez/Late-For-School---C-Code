// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap1.h"
#include "Trap1Info.h"

ATrap1::ATrap1() {
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor Component"));
	InteractorComponent->bIsPickable = true;
	InteractorComponent->bIsInteractable = false;

	ActionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("Action Component"));

	Info = CreateDefaultSubobject<UTrap1Info>(TEXT("Object Infos"));
}

void ATrap1::BeginPlay() {
	Super::BeginPlay();
}

void ATrap1::LoadMesh() {
	// This loads the skeletal asset.
	/*
	if (!MeshComponent)
	{
		USkeletalMeshComponent* SMeshComponent = NewObject<USkeletalMeshComponent>(this, USkeletalMeshComponent::StaticClass(), TEXT("MeshComponent"));
		USkeletalMesh* Mesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *Info->MeshReference));
		if (Mesh)
		{
			SMeshComponent->SetSkeletalMesh(Mesh);
		}
		MeshComponent = SMeshComponent;
		if (SMeshComponent) {
			SMeshComponent->RegisterComponent();
			SMeshComponent->SetRelativeLocation(FVector());
			SMeshComponent->SetRelativeRotation(FRotator());
			SMeshComponent->AttachTo(RootComponent, NAME_None, EAttachLocation::KeepRelativeOffset);
		}
	}
	*/
	Super::LoadMesh();
}


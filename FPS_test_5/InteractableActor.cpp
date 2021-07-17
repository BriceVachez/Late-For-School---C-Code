// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(FName(TEXT("Interactor")));
	LoadMesh();
	AttachCollider();
}

// Called when interacted with
bool AInteractableActor::Interact(UObjectInfo* info)
{
	return InteractorComponent->InteractWith(info);
}

// Called when tried to be picked up with
bool AInteractableActor::PickUp()
{
	return InteractorComponent->PickUp();
}

void AInteractableActor::LoadMesh() {
	if (!MeshComponent && !Info->MeshReference.Equals("")) {

		UStaticMeshComponent* SMeshComponent = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("MeshComponent"));
		UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *Info->MeshReference));
		if (Mesh)
		{
			SMeshComponent->SetStaticMesh(Mesh);
		}
		MeshComponent = SMeshComponent;
		if (SMeshComponent) {
			SMeshComponent->RegisterComponent();
			SMeshComponent->SetRelativeLocation(FVector(0, 0, 0));
			SMeshComponent->SetRelativeRotation(FRotator());
			SMeshComponent->AttachTo(RootComponent, NAME_None, EAttachLocation::KeepRelativeOffset);
		}
	}
}


void AInteractableActor::AttachCollider() {
	if (MeshComponent) {
		/*
		UBoxComponent* BoxComponent = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("BoxComponent"));
		if (BoxComponent) {
			BoxComponent->RegisterComponent();
			BoxComponent->SetRelativeLocation(FVector());
			BoxComponent->SetRelativeRotation(FRotator());
			BoxComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}*/
	}
}

void AInteractableActor::PlaySound(FString soundName, FVector location) {

}




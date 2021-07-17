// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "InteractorComponent.h"
#include "ActionComponent.h"
#include "ObjectInfo.h"

#include "InteractableActor.generated.h"

UCLASS()
class FPS_TEST_5_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	bool Interact(UObjectInfo* info);

	bool PickUp();

	virtual void LoadMesh();

	virtual void AttachCollider();

	virtual void PlaySound(FString soundName, FVector location);

	// Interactable component
	UPROPERTY(EditAnywhere)
		UInteractorComponent* InteractorComponent;

	// Action component
	UPROPERTY(EditAnywhere)
		UActionComponent* ActionComponent;

	// Object Infos
	UPROPERTY(VisibleAnywhere)
		UObjectInfo* Info;

	// Mesh
	UPROPERTY(VisibleDefaultsOnly)
		UMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UAudioComponent* AudioComponent;



};

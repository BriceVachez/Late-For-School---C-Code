// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ObjectInfo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_TEST_5_API UObjectInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectInfo();


	// Object Name
	UPROPERTY(EditAnywhere)
		FString Name;

	// Object Description
	UPROPERTY(EditAnywhere)
		FString Description;

	// Object ID used to define it
	UPROPERTY(EditAnywhere)
		FString ObjectId;

	// 3D String Mesh used for 3D render
	UPROPERTY(EditAnywhere)
		FString MeshReference;

	// 2D Image used for inventory/equiped item
	UPROPERTY(EditAnywhere)
		FString ImageReference;

	// Character that owns the object
	UPROPERTY(VisibleAnywhere)
		AActor* Player;

	virtual void UtilityFunction();

};
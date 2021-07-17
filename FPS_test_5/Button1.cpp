// Fill out your copyright notice in the Description page of Project Settings.


#include "Button1.h"
#include "ButtonInteractorComponent.h"
#include "Button1ActionComponent.h"

AButton1::AButton1() {

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InteractorComponent = CreateDefaultSubobject<UButtonInteractorComponent>(TEXT("Button Interactor Component"));
	InteractorComponent->bIsPickable = false;
	InteractorComponent->bIsInteractable = true;

	ActionComponent = CreateDefaultSubobject<UButton1ActionComponent>(TEXT("Button 1 Action Component"));

	Info = CreateDefaultSubobject<UObjectInfo>(TEXT("Object Infos"));
	Info->Name = "Button 1";
	Info->ObjectId = "button1";
	Info->Description = "First button";
	Info->MeshReference = "/Game/Asset/Sphere/Sphere_1.Sphere";
	Info->ImageReference = "none";
}


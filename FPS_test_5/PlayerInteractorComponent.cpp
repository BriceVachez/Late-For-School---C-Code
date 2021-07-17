// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractorComponent.h"

// Sets default values for this component's properties
UPlayerInteractorComponent::UPlayerInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UPlayerInteractorComponent::Interact(UObjectInfo* info) {
	AInteractableActor* actorToInteract = FindClosestInteractableActorWithRayTrace();
	if (actorToInteract == nullptr) {
		return false;
	}
	return actorToInteract->Interact(info);
}

AInteractableActor* UPlayerInteractorComponent::PickUp() {
	//AInteractableActor* actorToInteract = FindClosestInteractableActor();
	AInteractableActor* actorToPickUp = FindClosestInteractableActorWithRayTrace();
	if (actorToPickUp == nullptr) {
		return nullptr;
	}
	bool succeeded = actorToPickUp->PickUp();
	if (succeeded) {
		return actorToPickUp;
	}
	return nullptr;
}



AInteractableActor* UPlayerInteractorComponent::FindClosestInteractableActorWithRayTrace() {
	AInteractableActor* closestInteractableActor = nullptr;

	// First we need to do a Line Trace to check if we hit something

	// Try GetWorld()->GetFirstPlayerController()->GetPawn() if not working with GetOwner()
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace Params")), true, GetOwner());
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FVector CamLoc;
	FRotator CamRot;
	GetOwner()->GetActorEyesViewPoint(CamLoc, CamRot);

	FVector Start = CamLoc;
	FVector End = CamLoc + (CamRot.Vector() * MaxInteractionDistance);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Pawn,
		TraceParams
	);

	if (Hit.bBlockingHit) {
		if(Hit.GetComponent()->GetOwner()->ActorHasTag(FName(TEXT("Interactor")))) {
			AInteractableActor* actor = Cast<AInteractableActor>(Hit.GetActor());
			return actor;
		}
		return nullptr;
	}
	else {
		return nullptr;
	}

}


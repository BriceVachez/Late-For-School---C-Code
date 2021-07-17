// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap1Info.h"
#include "FPS_test_5Character.h"
#include "Trap1.h"

UTrap1Info::UTrap1Info() {
	Name = "Trap 1";
	ObjectId = "trap1";
	Description = "First trap";
	MeshReference = "StaticMesh'/Game/Asset/BearTrap/StaticBearTra/BearTrapToStatic.BearTrapToStatic'";
	ImageReference = "Texture2D'/Game/Asset/Images/bear_trap.bear_trap'";
}

void UTrap1Info::UtilityFunction() {
	// Step 1 : Find where the player is looking
	FHitResult RaycastHit = FindWherePlayerIsLooking();

	// Step 1.5 : Process result
	if (!RaycastHit.bBlockingHit) {
		return;
	}

	// Step 2 : Spawn an actor at location
	FVector Location = RaycastHit.ImpactPoint;
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ATrap1>(Location, Rotation, SpawnInfo);

	// Step 3 : Delete item from inventory
	AFPS_test_5Character* player = (AFPS_test_5Character*)GetWorld()->GetFirstPlayerController()->GetPawn();
	player->UnequipCurrentItem();
}

FHitResult UTrap1Info::FindWherePlayerIsLooking() {
	// Using Raycast

	// First we need to do a Line Trace to check if we hit something

	// Try GetWorld()->GetFirstPlayerController()->GetPawn() if not working with GetOwner()
	FCollisionQueryParams TraceParams = FCollisionQueryParams(
		FName(TEXT("Trace Params")),
		true,
		GetWorld()->GetFirstPlayerController()->GetPawn()
	);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FVector CamLoc;
	FRotator CamRot;
	GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorEyesViewPoint(CamLoc, CamRot);

	FVector Start = CamLoc;
	FVector End = CamLoc + (CamRot.Vector() * TrapPlacementDistance);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Pawn,
		TraceParams
	);

	return Hit;
}


// Copyright Epic Game, Inc. All Rights Reserved.

#include "FPS_test_5Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InventoryHUD.h"

//////////////////////////////////////////////////////////////////////////
// AFPS_test_5Character

AFPS_test_5Character::AFPS_test_5Character()
{
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	}

	InitializeInventory();

	equippedItemIndex = 0;

	InteractorComponent = CreateDefaultSubobject<UPlayerInteractorComponent>(TEXT("Interactor Component"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// FollowCamera->SetupAttachment(GetMesh(), FName("head"));
	FollowCamera->AttachTo(GetMesh(), "headSocket");
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(-10.0f, 20.0f, 3.5f));
	FollowCamera->SetRelativeRotation(FRotator(-90.0f, 20.0f, 90.0f));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPS_test_5Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPS_test_5Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPS_test_5Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AFPS_test_5Character::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPS_test_5Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_test_5Character::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPS_test_5Character::LookUpAtRate);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPS_test_5Character::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPS_test_5Character::Walk);

	// Equip
	PlayerInputComponent->BindAction("EquipDown", IE_Pressed, this, &AFPS_test_5Character::EquipDown);
	PlayerInputComponent->BindAction("EquipUp", IE_Pressed, this, &AFPS_test_5Character::EquipUp);

	// Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPS_test_5Character::Interact);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AFPS_test_5Character::PickUp);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AFPS_test_5Character::Use);
	PlayerInputComponent->BindAction("SwitchInventory", IE_Pressed, this, &AFPS_test_5Character::SwitchInventory);
	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AFPS_test_5Character::CatchMouseClick);
}

void AFPS_test_5Character::TurnAtRate(float Rate)
{
	if (bInventoryOpen) {
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPS_test_5Character::Turn(float Rate)
{
	if (bInventoryOpen) {
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate);
}

void AFPS_test_5Character::LookUpAtRate(float Rate)
{
	if (bInventoryOpen) {
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPS_test_5Character::LookUp(float Rate)
{
	if (bInventoryOpen) {
		return;
	}
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate);
}

void AFPS_test_5Character::MoveForward(float Value)
{
	if (bInventoryOpen) {
		return;
	}
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFPS_test_5Character::MoveRight(float Value)
{
	if (bInventoryOpen) {
		return;
	}
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AFPS_test_5Character::Sprint() {
	if (bInventoryOpen) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Sprinting"));

	// float sprintSpeed = 1500.0f;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AFPS_test_5Character::Walk() {
	if (bInventoryOpen) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Walking"));

	// float walkSpeed = 600.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


// Equip
void AFPS_test_5Character::EquipDown() {
	if (!bInventoryOpen) {
		return;
	}
	Equip((equippedItemIndex + 1) % 9);
}

void AFPS_test_5Character::EquipUp() {
	if (!bInventoryOpen) {
		return;
	}
	Equip((equippedItemIndex + 8) % 9);
}


void AFPS_test_5Character::Equip(int index) {
	equippedItemIndex = index;
	AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	inventoryHUD->equippedItemIndex = index;
	if (Inventory[index]) {
		inventoryHUD->DisplayName(Inventory[index]->Name);
	}
}

void AFPS_test_5Character::Interact() {
	if (bInventoryOpen) {
		return;
	}

	UObjectInfo* objectToUse = Inventory[equippedItemIndex];
	if (objectToUse) {
		InteractorComponent->Interact(objectToUse);
	} else if(GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Object is nullptr."));
	}
}

void AFPS_test_5Character::PickUp() {
	if (bInventoryOpen) {
		return;
	}
	int freeIndexInInventory = FindFirstInventorySpace();
	if (freeIndexInInventory == -1) {
		// Add something to say it's full
	}
	else {
		AInteractableActor* pickedUpObject = InteractorComponent->PickUp();

		if (pickedUpObject != nullptr) {
			UObjectInfo* info = pickedUpObject->Info;
			info->Player = this;
			AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			inventoryHUD->ChangeSlot(freeIndexInInventory, info->ImageReference);
			UObjectInfo* newInfo = NewObject<UObjectInfo>(this, FName(*info->Name));
			newInfo->ObjectId = info->ObjectId;
			newInfo->Name = info->Name;
			newInfo->Description = info->Description;
			newInfo->MeshReference = info->MeshReference;
			newInfo->ImageReference = info->ImageReference;
			Inventory[freeIndexInInventory] = newInfo;
			pickedUpObject->Destroy();
		}

	}
}

void AFPS_test_5Character::Use() {
	if (bInventoryOpen) {
		return;
	}
	Inventory[equippedItemIndex]->UtilityFunction();
}

void AFPS_test_5Character::SwitchInventory() {
	AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (inventoryHUD->bIsStorageOpen) {
		return;
	}
	inventoryHUD->ChangeInventoryState();

	APlayerController* controller = (APlayerController*)GetController();

	if (controller)
	{
		controller->bShowMouseCursor = false;
	}
}

void AFPS_test_5Character::CatchMouseClick() {
	if (bInventoryOpen) {
		APlayerController* controller = (APlayerController*)GetController();

		float mouseX;
		float mouseY;
		controller->GetMousePosition(mouseX, mouseY);

		// Check where we clicked
		AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		int index = inventoryHUD->InventoryIndexClicked(mouseX, mouseY);


		if (index == -1 && inventoryHUD->bIsStorageOpen) {

			index = inventoryHUD->StorageSlotClicked(mouseX, mouseY);

			if (index != -1) {
				if (IndexSelected == -1) {
					IsFirstSlotInStorage = true;
				}
				else {
					IsSecondSlotInStorage = true;

				}
			}
			else {
				if (inventoryHUD->HitReturnButton(mouseX, mouseY)) {
					FullyCloseInventory();
					ALocker1* locker = nullptr;
					for (TObjectIterator<ALocker1> Itr; Itr; ++Itr) {
						if (Itr->IsA(ALocker1::StaticClass())) {
							locker = *Itr;
							locker->PlaySound("closing", locker->GetActorLocation());
							break;
						}
					}
				}
				IndexSelected = -1;
			}
		}
		if (index == -1) {
			IndexSelected = -1;
			IsFirstSlotInStorage = false;
			IsSecondSlotInStorage = false;
		}

		// Select what item is clicked
		if (IndexSelected == -1) {
			IndexSelected = index;
		}

		// If an item is already selected, invert both
		else {

			oldItemAtIndex = NewObject<UObjectInfo>(UObjectInfo::StaticClass(), FName("Inventory Object"));
			oldItemAtNewIndex = NewObject<UObjectInfo>(UObjectInfo::StaticClass(), FName("Inventory Object"));
			ALocker1* locker = nullptr;
			for (TObjectIterator<ALocker1> Itr; Itr; ++Itr) {
				if (Itr->IsA(ALocker1::StaticClass())) {
					locker = *Itr;
					break;
				}
			}
			if (IsFirstSlotInStorage) {
				int x1 = IndexSelected % locker->StorageSizeX;
				int y1 = IndexSelected / locker->StorageSizeX;
			}
			if (IsSecondSlotInStorage) {
				int x2 = index % locker->StorageSizeX;
				int y2 = index / locker->StorageSizeX;
			}
			// First, check where we clicked
			if (IsFirstSlotInStorage) {
				// Find locker and pickup item
				int x1 = IndexSelected % locker->StorageSizeX;
				int y1 = IndexSelected / locker->StorageSizeX;
				oldItemAtIndex = locker->PickupItem(x1, y1);
			}
			else {
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Index Selected : %f"), (float)IndexSelected));
				}
				/*oldItemAtIndex->Name = FString(Inventory[IndexSelected]->Name);
				oldItemAtIndex->ObjectId = FString(Inventory[IndexSelected]->ObjectId);
				oldItemAtIndex->Description = FString(Inventory[IndexSelected]->Description);
				oldItemAtIndex->ImageReference = FString(Inventory[IndexSelected]->ImageReference);
				oldItemAtIndex->MeshReference = FString(Inventory[IndexSelected]->MeshReference);
				oldItemAtIndex->Player = Inventory[IndexSelected]->Player;*/
				oldItemAtIndex = Inventory[IndexSelected];
			}
			if (IsSecondSlotInStorage) {
				// Find locker and pickup item
				int x2 = index % locker->StorageSizeX;
				int y2 = index / locker->StorageSizeX;

				oldItemAtNewIndex = locker->PickupItem(x2, y2);
			}
			else {
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Index : %f"), (float)index));
				}
				/*oldItemAtNewIndex->Name = FString(Inventory[index]->Name);
				oldItemAtNewIndex->ObjectId = FString(Inventory[index]->ObjectId);
				oldItemAtNewIndex->Description = FString(Inventory[index]->Description);
				oldItemAtNewIndex->ImageReference = FString(Inventory[index]->ImageReference);
				oldItemAtNewIndex->MeshReference = FString(Inventory[index]->MeshReference);
				oldItemAtNewIndex->Player = Inventory[index]->Player;*/
				oldItemAtNewIndex = Inventory[index];
			}
			if (oldItemAtNewIndex == nullptr || oldItemAtIndex == nullptr) {
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("On a du nullptr"));
				}
				IndexSelected = -1;
				IsFirstSlotInStorage = false;
				IsSecondSlotInStorage = false;
				return;
			}
			if (IsFirstSlotInStorage) {
				int x1 = IndexSelected % locker->StorageSizeX;
				int y1 = IndexSelected / locker->StorageSizeX;
				inventoryHUD->ChangeStorageSlot(IndexSelected, oldItemAtNewIndex->ImageReference);
				locker->AddItem(oldItemAtNewIndex, x1, y1);
			}
			else {
				inventoryHUD->ChangeSlot(IndexSelected, oldItemAtNewIndex->ImageReference);
				Inventory[IndexSelected] = oldItemAtNewIndex;
			}

			if (IsSecondSlotInStorage) {
				int x2 = index % locker->StorageSizeX;
				int y2 = index / locker->StorageSizeX;
				inventoryHUD->ChangeStorageSlot(index, oldItemAtIndex->ImageReference);
				locker->AddItem(oldItemAtIndex, x2, y2);
			}
			else {
				inventoryHUD->ChangeSlot(index, oldItemAtIndex->ImageReference);
				Inventory[index] = oldItemAtIndex;
			}

			IndexSelected = -1;
			IsFirstSlotInStorage = false;
			IsSecondSlotInStorage = false;
		}
	}
}

UObjectInfo* AFPS_test_5Character::UnequipCurrentItem() {
	return UnequipItem(equippedItemIndex);
}

UObjectInfo* AFPS_test_5Character::UnequipItem(int index) {
	UObjectInfo* unequippedItem = Inventory[index];

	UObjectInfo* noneObject;
	noneObject = NewObject<UObjectInfo>(UObjectInfo::StaticClass(), TEXT("None Object"));
	noneObject->Name = "noneObject";
	noneObject->Description = "none";
	noneObject->ObjectId = "none";
	noneObject->MeshReference = "none";
	noneObject->ImageReference = "/Game/Asset/Images/none.Texture2D_0";
	noneObject->Player = this;

	Inventory[index] = noneObject;

	AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	inventoryHUD->ChangeSlot(index, noneObject->ImageReference);

	return unequippedItem;
}

void AFPS_test_5Character::InitializeInventory() {
	UObjectInfo* noneObject;
	noneObject = CreateDefaultSubobject<UObjectInfo>(TEXT("None Object"));
	noneObject->Name = "noneObject";
	noneObject->Description = "none";
	noneObject->ObjectId = "none";
	noneObject->MeshReference = "none";
	noneObject->ImageReference = "/Game/Asset/Images/none.Texture2D_0";
	noneObject->Player = this;

	for (int i = 0; i < 9; ++i) {
		Inventory.Add(noneObject);
	}
}

int AFPS_test_5Character::FindFirstInventorySpace() {
	for (int i = 0; i < 9; ++i) {
		if (Inventory[i] && Inventory[i]->ObjectId == "none") {
			return i;
		}
	}
	return -1;
}

void AFPS_test_5Character::InventoryIsOpen() {
	APlayerController* controller = (APlayerController*)GetController();

	if (controller)
	{
		controller->bShowMouseCursor = true;
		bInventoryOpen = true;
	}
}

void AFPS_test_5Character::InventoryIsClosed() {
	APlayerController* controller = (APlayerController*)GetController();

	if (controller)
	{
		controller->bShowMouseCursor = false;
		bInventoryOpen = false;
	}
}

void AFPS_test_5Character::FullyOpenInventory() {
	AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	inventoryHUD->OpenStorage();
}


void AFPS_test_5Character::FullyCloseInventory() {
	AInventoryHUD* inventoryHUD = Cast<AInventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	inventoryHUD->CloseStorage();
}

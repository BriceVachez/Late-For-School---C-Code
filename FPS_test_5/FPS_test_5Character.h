// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObjectInfo.h"
#include "PlayerInteractorComponent.h"

#include "FPS_test_5Character.generated.h"

UCLASS(config=Game)
class AFPS_test_5Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AFPS_test_5Character();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere)
		float WalkSpeed;

	UPROPERTY(EditAnywhere)
		float SprintSpeed;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	void Turn(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	void LookUp(float Rate);

	void Sprint();

	void Walk();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:

	// Component used for interaction
	UPROPERTY(VisibleAnywhere)
		UPlayerInteractorComponent* InteractorComponent;

	//TODO : this is only for test
	UPROPERTY(EditAnywhere)
		TArray<UObjectInfo*> Inventory;

	UPROPERTY(EditAnywhere)
		UObjectInfo* oldItemAtNewIndex;

	UPROPERTY(EditAnywhere)
		UObjectInfo* oldItemAtIndex;


	//TODO : this is only for test
	UPROPERTY(EditAnywhere)
		int equippedItemIndex;

	void EquipDown();
	void EquipUp();
	void Equip(int index);

	void Interact();
	void PickUp();
	void Use();

	void SwitchInventory();

	UObjectInfo* UnequipCurrentItem();
	UObjectInfo* UnequipItem(int index);

	void CatchMouseClick();

private:

	void InitializeInventory();

	// Returns the index of the first empty inventory space
	UFUNCTION()
		int FindFirstInventorySpace();

public:
	void FullyOpenInventory();
	void FullyCloseInventory();
	void InventoryIsOpen();
	void InventoryIsClosed();

protected:
	bool bInventoryOpen = false;
	int IndexSelected = -1;
	bool IsFirstSlotInStorage = false;
	bool IsSecondSlotInStorage = false;


};


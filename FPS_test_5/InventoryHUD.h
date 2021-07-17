// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h" 

#include "Locker1.h"
#include "InventoryHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_5_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:

    TArray<FCanvasTileItem> InventorySlots;

    // This will be drawn at the bottom.
    UPROPERTY(EditDefaultsOnly)
        UTexture2D* InventoryBackground;

    UPROPERTY(EditAnywhere)
        int OpeningDuration = 2.0f;

    UPROPERTY(EditAnywhere)
        int ClosingDuration = 2.0f;

    //Position of the inventry background
    float InventoryPosX;
    float InventoryPosY;

    //Sizes of the inventory background
    float InventorySizeX;
    float InventorySizeY;

    //Offset during the animation
    float OffsetY = 0.2f;

    // Used to only initialize slots once
    bool bIsInitialized = false;

    // Current player equipped item
    int equippedItemIndex = 0;

    // Primary draw call for the HUD.
    virtual void DrawHUD() override;

    void InitializeSlots();
    void ChangeSlot(int slotPosition, FString newImageRef);
    void DrawSlots();
    void ChangedEquippedSlot(int index);
    void DrawEquippedSlot();

    UFUNCTION()
        void ChangeInventoryState();

    int InventoryIndexClicked(float mousePosX, float mousePosY);

    // Equip text
    UPROPERTY(VisibleAnywhere)
        FString NameToDisplay = "C le non";

    void DisplayName(FString nameToDisplay);


protected:

    void OpenInventory();
    void CloseInventory();

    FTimerHandle InventoryOpeningHandle;
    FTimerHandle InventoryClosingHandle;

    void AdvanceOpening();
    void AdvanceClosing();

    void FinishOpening();
    void FinishClosing();

    UPROPERTY(VisibleAnywhere)
        bool IsChangingState = false;

    UPROPERTY(VisibleAnywhere)
        bool IsOpen = false;

    void FullyOpenInventory();
    void FullyCloseInventory();

    FTimerHandle NameDisplayHandle;

    UPROPERTY(EditAnywhere)
        float DisplayDuration = 3.0f;
    void UndisplayName();
    void DrawName();

    UPROPERTY(EditAnywhere)
        bool bDisplayName = false;

// Storage part
public:

    TArray<FCanvasTileItem> StorageSlots;

    //Position of the storage background
    float StoragePosX;
    float StoragePosY;

    //Sizes of the storage background
    float StorageSizeX;
    float StorageSizeY;

    // Used to only initialize slots once

    UPROPERTY(EditAnywhere)
        bool bIsStorageOpen = false;

    void OpenStorage();
    void CloseStorage();
    
    void InitializeStorageSlots();
    void ChangeStorageSlot(int slotPosition, FString newImageRef);
    void DrawButton();
    void DrawStorageSlots();
    int StorageSlotClicked(float mousePosX, float mousePosY);

    bool HitReturnButton(float mousePosX, float mousePosY);

protected:

    const int StorageSlotsX = 9;
    const int StorageSlotsY = 5;

    // Return button
    float ButtonPosX;
    float ButtonPosY;
    float ButtonSizeX;
    float ButtonSizeY;

    UPROPERTY(EditAnywhere)
        FString ButtonImageReference = "Texture2D'/Game/Asset/Images/return_take0.return_take0'";

	
};

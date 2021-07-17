// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHUD.h"
#include "Blueprint/UserWidget.h"
#include "ObjectInfo.h"
#include "FPS_test_5Character.h"


void AInventoryHUD::DrawHUD()
{
	Super::DrawHUD();

	InventoryBackground = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/Asset/Images/background.background")));

	if (InventoryBackground)
	{
		InventoryPosX = Canvas->ClipX * 0.2f;
		InventoryPosY = Canvas->ClipY * (0.8f + OffsetY);
		FVector2D BackgroundDrawPosition(InventoryPosX, InventoryPosY);

		FCanvasTileItem TileItem(BackgroundDrawPosition, InventoryBackground->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		InventorySizeX = Canvas->ClipX * 0.6f;
		InventorySizeY = Canvas->ClipX * 0.07f;
		TileItem.Size = FVector2D(InventorySizeX, InventorySizeY);
		Canvas->DrawItem(TileItem);

		if (bIsStorageOpen) {
			StoragePosX = Canvas->ClipX * 0.2f;
			StoragePosY = Canvas->ClipY * 0.02f;
			FVector2D StorageBackgroundDrawPosition(StoragePosX, StoragePosY);

			FCanvasTileItem StorageBackgroundTileItem(StorageBackgroundDrawPosition, InventoryBackground->Resource, FLinearColor::White);
			StorageBackgroundTileItem.BlendMode = SE_BLEND_Translucent;
			StorageSizeX = Canvas->ClipX * 0.6f;
			StorageSizeY = Canvas->ClipY * 0.75f;
			StorageBackgroundTileItem.Size = FVector2D(StorageSizeX, StorageSizeY);
			Canvas->DrawItem(StorageBackgroundTileItem);
		}
	}

	if (!bIsInitialized) {
		InitializeSlots();
	}
	DrawEquippedSlot();
	DrawSlots();

	if (bIsStorageOpen) {
		DrawStorageSlots();
		DrawButton();
	}
	//DrawName();
	if (bDisplayName) {
		DrawName();
	}

}

void AInventoryHUD::InitializeSlots() {

	FVector2D tilePosition;
	float tileSize = 0.1f * InventorySizeX;
	// Offset from background
	float tileBaseOffsetX = 0.01f * InventorySizeX; //1% of background
	float tileBaseOffsetY = (InventorySizeY - tileSize) / 2.0f;

	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/Asset/Images/none.Texture2D_0")));

	for (int i = 0; i < 9; ++i) {
		float dynamicOffsetX = 0.11f * InventorySizeX * i;
		float tilePositionX = InventoryPosX + tileBaseOffsetX + dynamicOffsetX;
		float tilePositionY = InventoryPosY + tileBaseOffsetY;
		tilePosition = FVector2D(tilePositionX, tilePositionY);

		FCanvasTileItem TileItem(tilePosition, texture->Resource, FLinearColor::White);
		TileItem.Size = FVector2D(tileSize, tileSize);
		TileItem.BlendMode = SE_BLEND_Translucent;
		InventorySlots.Add(TileItem);
		//Canvas->DrawItem(TileItem);
	}

	tileSize = 0.1f * StorageSizeX;
	//Offset from background
	tileBaseOffsetX = 0.01f * StorageSizeX;
	tileBaseOffsetY = 0.02f * StorageSizeY;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 5; ++j) {
			float dynamicOffsetX = 0.11f * StorageSizeX * i;
			float dynamicOffsetY = (tileSize + (0.25f * (StorageSizeY - 5.0f * tileSize - 2.0f * tileBaseOffsetY))) * j;
			float tilePositionX = StoragePosX + tileBaseOffsetX + dynamicOffsetX;
			float tilePositionY = StoragePosY + tileBaseOffsetY + dynamicOffsetY;
			tilePosition = FVector2D(tilePositionX, tilePositionY);

			FCanvasTileItem TileItem(tilePosition, texture->Resource, FLinearColor::White);
			TileItem.Size = FVector2D(tileSize, tileSize);
			TileItem.BlendMode = SE_BLEND_Translucent;
			StorageSlots.Add(TileItem);
		}
	}
	bIsInitialized = true;
}

void AInventoryHUD::ChangeSlot(int slotPosition, FString newImageRef) {

	FCanvasTileItem tileToReplace = InventorySlots[slotPosition];

	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *newImageRef));

	if (texture) {
		FCanvasTileItem newTile(tileToReplace.Position, texture->Resource, FLinearColor::White);
		InventorySlots[slotPosition] = newTile;
	}

}

void AInventoryHUD::ChangeStorageSlot(int slotPosition, FString newImageRef) {
	FCanvasTileItem tileToReplace = StorageSlots[slotPosition];

	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *newImageRef));

	FCanvasTileItem newTile(tileToReplace.Position, texture->Resource, FLinearColor::White);
	StorageSlots[slotPosition] = newTile;

}

void AInventoryHUD::DrawSlots() {
	float tileSize = 0.1f * InventorySizeX;
	// Offset from background
	float tileBaseOffsetX = 0.01f * InventorySizeX; //1% of background
	float tileBaseOffsetY = (InventorySizeY - tileSize) / 2.0f;
	for (int i = 0; i < InventorySlots.Num(); ++i) {
		float dynamicOffsetX = 0.11f * InventorySizeX * i;
		float tilePositionX = InventoryPosX + tileBaseOffsetX + dynamicOffsetX;
		float tilePositionY = InventoryPosY + tileBaseOffsetY;
		FCanvasTileItem tile = InventorySlots[i];
		tile.Position = FVector2D(tilePositionX, tilePositionY);
		tile.Size = FVector2D(0.1f * Canvas->ClipX * 0.6f, 0.1f * Canvas->ClipX * 0.6f);
		tile.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(tile);
	}

}

void AInventoryHUD::DrawStorageSlots() {
	float tileSize = 0.1f * StorageSizeX;
	// Offset from background
	float tileBaseOffsetX = 0.01f * StorageSizeX;
	float tileBaseOffsetY = 0.02f * StorageSizeY;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 5; ++j) {
			float dynamicOffsetX = 0.11f * StorageSizeX * i;
			float dynamicOffsetY = (tileSize + (0.25f * (StorageSizeY - 5.0f * tileSize - 2.0f * tileBaseOffsetY))) * j;
			float tilePositionX = StoragePosX + tileBaseOffsetX + dynamicOffsetX;
			float tilePositionY = StoragePosY + tileBaseOffsetY + dynamicOffsetY;
			FCanvasTileItem tile = StorageSlots[9 * j + i];
			tile.Position = FVector2D(tilePositionX, tilePositionY);
			tile.Size = FVector2D(0.1f * Canvas->ClipX * 0.6f, 0.1f * Canvas->ClipX * 0.6f);
			tile.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(tile);
		}
	}

}

void AInventoryHUD::DrawButton() {
	ButtonPosX = Canvas->ClipX * 0.85f;
	ButtonPosY = Canvas->ClipY * 0.6f;
	ButtonSizeX = Canvas->ClipX * 0.1f;
	ButtonSizeY = Canvas->ClipY * 0.1f;

	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *ButtonImageReference));

	FCanvasTileItem TileItem(FVector2D(ButtonPosX, ButtonPosY), texture->Resource, FLinearColor::White);
	TileItem.Size = FVector2D(ButtonSizeX, ButtonSizeY);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

bool AInventoryHUD::HitReturnButton(float mousePosX, float mousePosY) {
	return ((mousePosX >= ButtonPosX && mousePosX <= ButtonPosX + ButtonSizeX) &&
		(mousePosY >= ButtonPosY && mousePosY <= ButtonPosY + ButtonSizeY));
}

void AInventoryHUD::ChangedEquippedSlot(int index) {
	equippedItemIndex = index;
}

void AInventoryHUD::DrawEquippedSlot() {
	UTexture2D* texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("/Game/Asset/Images/equipped.equipped")));

	float tileBaseOffsetX = 0.005f * InventorySizeX; //0.5% of background
	float dynamixOffsetX = equippedItemIndex * (0.11f * InventorySizeX);

	float posX = InventoryPosX + tileBaseOffsetX + dynamixOffsetX;
	float posY = InventoryPosY;

	FVector2D tilePosition(posX, posY);
	FCanvasTileItem TileItem(tilePosition, texture->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.Size = FVector2D(0.11f * InventorySizeX, InventorySizeY);
	Canvas->DrawItem(TileItem);
}

void AInventoryHUD::ChangeInventoryState() {
	if (IsChangingState) {
		return;
	}
	DisplayName("");
	IsChangingState = true;
	if (IsOpen) {
		CloseInventory();
	}
	else {
		OpenInventory();
	}
}

void AInventoryHUD::OpenInventory() {
	GetWorldTimerManager().SetTimer(InventoryOpeningHandle, this, &AInventoryHUD::AdvanceOpening, OpeningDuration / 120.0f, true);
}

void AInventoryHUD::CloseInventory() {
	GetWorldTimerManager().SetTimer(InventoryClosingHandle, this, &AInventoryHUD::AdvanceClosing, ClosingDuration / 120.0f, true);
}

void AInventoryHUD::AdvanceOpening() {
	OffsetY -= 0.2f / 120.0f;
	if (OffsetY <= 0.0f) {
		FinishOpening();
	}
}

void AInventoryHUD::FinishOpening() {
	GetWorldTimerManager().ClearTimer(InventoryOpeningHandle);
	FullyOpenInventory();
}

void AInventoryHUD::FullyOpenInventory() {
	OffsetY = 0.0f;
	IsOpen = true;
	IsChangingState = false;
	Cast<AFPS_test_5Character>(GetWorld()->GetFirstPlayerController()->GetPawn())->InventoryIsOpen();
}

void AInventoryHUD::FullyCloseInventory() {
	OffsetY = 0.2f;
	IsOpen = false;
	IsChangingState = false;
	Cast<AFPS_test_5Character>(GetWorld()->GetFirstPlayerController()->GetPawn())->InventoryIsClosed();
}

void AInventoryHUD::AdvanceClosing() {
	OffsetY += 0.2f / 120.0f;
	if (OffsetY >= 0.2f) {
		FinishClosing();
	}
}

void AInventoryHUD::FinishClosing() {
	GetWorldTimerManager().ClearTimer(InventoryClosingHandle);
	OffsetY = 0.2f;
	IsChangingState = false;
	IsOpen = false;
	Cast<AFPS_test_5Character>(GetWorld()->GetFirstPlayerController()->GetPawn())->InventoryIsClosed();
}

int AInventoryHUD::InventoryIndexClicked(float mousePosX, float mousePosY) {
	float tileSize = 0.1f * InventorySizeX;
	float tileBaseOffsetX = 0.005f * InventorySizeX; //0.5% of background
	float dynamicOffsetX = 0.11f * InventorySizeX;
	float tileBaseOffsetY = (InventorySizeY - tileSize) / 2.0f;
	if (mousePosY < (InventoryPosY + tileBaseOffsetY) || mousePosY >(InventoryPosY + tileBaseOffsetY + tileSize)) {
		// Case not in the right Y range
		return -1;
	}
	else if (mousePosX < (InventoryPosX + tileBaseOffsetX) || mousePosX >(InventoryPosX + InventorySizeX - tileBaseOffsetX)) {
		// Case not in the right X range 
		return -1;
	}
	else {
		for (int index = 0; index < InventorySlots.Num(); ++index) {
			if (mousePosX > (InventoryPosX + tileBaseOffsetX + index * dynamicOffsetX) &&
				mousePosX < (InventoryPosX + tileBaseOffsetX + tileSize + index * dynamicOffsetX)) {
				return index;
			}
		}
		return -1;
	}
}

int AInventoryHUD::StorageSlotClicked(float mousePosX, float mousePosY) {
	float tileSize = 0.1f * StorageSizeX;
	float tileBaseOffsetX = 0.01f * StorageSizeX;
	float tileBaseOffsetY = 0.02f * StorageSizeY;
	float dynamicOffsetX = 0.11f * StorageSizeX;
	float dynamicOffsetY = (tileSize + (0.25f * (StorageSizeY - 5.0f * tileSize - 2.0f * tileBaseOffsetY)));
	if (mousePosY < (StoragePosY + tileBaseOffsetY) || mousePosY >(StoragePosY + StorageSizeY - tileBaseOffsetY)) {
		// Case not in the right Y range

		return -1;
	}
	else if (mousePosX < (StoragePosX + tileBaseOffsetX) || mousePosX >(StoragePosX + StorageSizeX - tileBaseOffsetX)) {
		// Case not in the right X range         
		return -1;
	}
	else {
		for (int indexX = 0; indexX < StorageSlotsX; ++indexX) {
			if (mousePosX > (StoragePosX + tileBaseOffsetX + indexX * dynamicOffsetX) &&
				mousePosX < (StoragePosX + tileBaseOffsetX + tileSize + indexX * dynamicOffsetX)) {
				for (int indexY = 0; indexY < StorageSlotsY; ++indexY) {
					if (mousePosY > (StoragePosY + tileBaseOffsetY + indexY * dynamicOffsetY) &&
						mousePosY < (StoragePosY + tileBaseOffsetY + tileSize + indexY * dynamicOffsetY)) {
						return (indexY * StorageSlotsX + indexX);
					}
				}
				return -1;
			}
		}
		return -1;
	}
	return -1;
}

void AInventoryHUD::OpenStorage() {
	bIsStorageOpen = true;
	FullyOpenInventory();
}


void AInventoryHUD::CloseStorage() {
	bIsStorageOpen = false;
	FullyCloseInventory();
}

void AInventoryHUD::DisplayName(FString nameToDisplay) {
	if (GetWorldTimerManager().IsTimerActive(NameDisplayHandle)) {
		GetWorldTimerManager().ClearTimer(NameDisplayHandle);
	}
	if (nameToDisplay.Equals("none") || nameToDisplay.Equals("noneObject")) {
		nameToDisplay = "";
	}
	NameToDisplay = nameToDisplay;
	bDisplayName = true;
	GetWorldTimerManager().SetTimer(NameDisplayHandle, this, &AInventoryHUD::UndisplayName, DisplayDuration, true);
}

void AInventoryHUD::UndisplayName() {
	bDisplayName = false;
	GetWorldTimerManager().ClearTimer(NameDisplayHandle);

}

void AInventoryHUD::DrawName() {

	float NamePlacementX = Canvas->ClipX * 0.2f;
	float NamePlacementY = Canvas->ClipY * 0.7f;

	DrawText(NameToDisplay, FColor::White, NamePlacementX, NamePlacementY, (UFont*)0, 3.0f);
}
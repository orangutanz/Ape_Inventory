// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum ItemType
{
	Equipment        UMETA(DisplayName = "Equipment"),
	Consumable       UMETA(DisplayName = "Consumable"),
	MaterialItem     UMETA(DisplayName = "MaterialItem"),
	Container        UMETA(DisplayName = "Container"),
	Miscellaneous    UMETA(DisplayName = "Miscellaneous")
};
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class APE_INVENTORY_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FName itemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TEnumAsByte<ItemType> itemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int maxStack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int Quantity = 0;

	UPROPERTY()
	class UInventoryComponent* OwnerInventory;

	virtual void Use(class AApe_InventoryCharacter* Character) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AApe_InventoryCharacter* Character);
};

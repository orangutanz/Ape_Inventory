// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class AApe_InventoryCharacter;

UENUM(BlueprintType)
enum ItemType
{
	Consumable       UMETA(DisplayName = "Consumable"),
	Container        UMETA(DisplayName = "Container"),
	Equipment        UMETA(DisplayName = "Equipment"),
	Material		 UMETA(DisplayName = "Material"),
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
	UItem();
	~UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TEnumAsByte<ItemType> ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (ClampMin = 0))
	int32 MaxStack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int32 Quantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInventoryComponent* OwnerInventory;

	virtual void Use(AApe_InventoryCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(AApe_InventoryCharacter* Character);

	UFUNCTION(BlueprintCallable)
	UItem* SplitItem(int32 num);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class AApe_InventoryCharacter;

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
	UItem();
	~UItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TEnumAsByte<ItemType> ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Icon;

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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UInventoryComponent;

UENUM(BlueprintType)
enum EItemType
{
	Consumable       UMETA(DisplayName = "Consumable"),
	Equipment        UMETA(DisplayName = "Equipment"),
	Misc		     UMETA(DisplayName = "Misc")
};


USTRUCT(BlueprintType)
struct APE_INVENTORY_API FItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ape_Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ape_Item", meta = (ClampMin = 0))
	int32 MaxStack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ape_Item", meta = (ClampMin = 0))
	int32 Quantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ape_Item")
	TEnumAsByte<EItemType> ItemType;

};


UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class APE_INVENTORY_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ape_Item")
	void SetItemInfo(FItemInfo info);

	UFUNCTION(BlueprintCallable, Category = "Ape_Item")
	bool SetQuantity(int32 num);

	UFUNCTION(BlueprintCallable, Category = "Ape_Item")
	FItemInfo GetItemInfo() { return mItemInfo; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ape_Item")
	FORCEINLINE FName GetItemID() const { return  mItemInfo.ItemID; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ape_Item")
	FORCEINLINE int32 GetMaxStack() const { return mItemInfo.MaxStack; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ape_Item")
	FORCEINLINE int32 GetQuantity() const { return mItemInfo.Quantity; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ape_Item")
	FORCEINLINE TEnumAsByte<EItemType> GetItemType() const { return mItemInfo.ItemType; }

	/** Return null if (num > Quantity) || (MaxStack == 1) || (num == 0)	*/
	UFUNCTION(BlueprintCallable, Category = "Ape_Item")
	UItem* SplitItem(int32 num);

private:
	FItemInfo mItemInfo;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class AApe_InventoryCharacter;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (ClampMin = 0))
	int32 MaxStack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int32 Quantity = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TEnumAsByte<EItemType> ItemType;

};


UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class APE_INVENTORY_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Item")
	void InitItemInfo(FItemInfo info);

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool SetQuantity(int32 num);

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	//FName ItemID;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (ClampMin = 0))
	//int32 MaxStack = 1;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	//int32 Quantity = 1;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	//TEnumAsByte<EItemType> ItemType;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FItemInfo GetItemInfo() { return mItemInfo; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE FName GetItemID() const { return  mItemInfo.ItemID; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE int32 GetMaxStack() const { return mItemInfo.MaxStack; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE int32 GetQuantity() const { return mItemInfo.Quantity; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE TEnumAsByte<EItemType> GetItemType() const { return mItemInfo.ItemType; }

	/** Return null if (num > Quantity) || (MaxStack == 1) || (num == 0)	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItem* SplitItem(int32 num);

private:
	FItemInfo mItemInfo;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Consumable.generated.h"

class AApe_InventoryCharacter;

UENUM(BlueprintType)
enum ConsumableType
{
	Food        UMETA(DisplayName = "Food"),
	Health      UMETA(DisplayName = "Health"),
	Mana		UMETA(DisplayName = "Mana"),
	Stamina     UMETA(DisplayName = "Stamina"),
	Other       UMETA(DisplayName = "Other")
};

UCLASS()
class APE_INVENTORY_API UItem_Consumable : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 regenAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TEnumAsByte<ConsumableType> ConsumableType;

protected:
	virtual void Use(class AApe_InventoryCharacter* character) override;
};

USTRUCT(BlueprintType)
struct FConsumableInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName itemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TEnumAsByte<ItemType> itemType = ItemType::Consumable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 regenAmount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TEnumAsByte<ConsumableType> ConsumableType;
};
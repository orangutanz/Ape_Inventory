#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Equipment.generated.h"

class AApe_InventoryCharacter;

UCLASS(BlueprintType)
class APE_INVENTORY_API UItem_Equipment : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 Damage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int32 Defense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int32 maxDurability = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0))
	int32 curDurability = 300;

protected:
	virtual void Use(AApe_InventoryCharacter* character) override;
	
};

//this is what data will be stored and pulled from
USTRUCT(BlueprintType)
struct FEquipmentInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName itemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TEnumAsByte<ItemType> itemType = ItemType::Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (ClampMin = 0))
	int32 maxDurability;
};
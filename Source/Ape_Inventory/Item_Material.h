#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Material.generated.h"


UCLASS(BlueprintType)
class APE_INVENTORY_API UItem_Material : public UItem
{
	GENERATED_BODY()
public:

protected:
};


//this is what data will be stored and pulled from
USTRUCT(BlueprintType)
struct FMaterialInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName itemID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TEnumAsByte<ItemType> itemType = ItemType::MaterialItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (ClampMin = 0))
	int32 maxStack = 64;
};
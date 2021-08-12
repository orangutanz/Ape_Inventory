#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item_Material.h"
#include "ItemData_Material.generated.h"

UCLASS(BlueprintType)
class APE_INVENTORY_API UItemData_Material : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<FMaterialInfo> MaterialDatabase;
};

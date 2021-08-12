#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item_Equipment.h"
#include "ItemData_Equipment.generated.h"

UCLASS(BlueprintType)
class APE_INVENTORY_API UItemData_Equipment : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<FEquipmentInfo> EquipmentDatabase;

};

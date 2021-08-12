#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Equipment.generated.h"

class AApe_InventoryCharacter;

UCLASS()
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
	virtual void Use(class AApe_InventoryCharacter* character) override;
	
};

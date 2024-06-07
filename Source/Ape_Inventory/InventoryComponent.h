#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APE_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	bool AddItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	bool RemoveItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	bool SwapItemByIndex(const int32 a, const int32 b);

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	void SortItems();

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	void TransferItems(UInventoryComponent* toInventory);

	//Find item
	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	UItem* FindItemID(FName name, int32& index);

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	bool Contains(UItem* item, int& index);

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	void UpdateInventory() { OnInventoryUpdated.Broadcast(); }

	UFUNCTION(BlueprintCallable, Category = "Ape_Inventory")
	TArray<FItemInfo> GetItemInfos();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ape_Inventory")
	TArray<UItem*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ape_Inventory")
	int32 MaxSize = 20;

	UPROPERTY(BlueprintAssignable, Category = "Ape_Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};

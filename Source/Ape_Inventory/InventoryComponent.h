#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

UENUM(BlueprintType)
enum AddItemResult
{
	Success		UMETA(DisplayName = "Success"),
	Partial		UMETA(DisplayName = "Partial"),
	Fail		UMETA(DisplayName = "Fail")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APE_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UItem* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SwapItemByIndex(const int32 a, const int32 b);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TransferItemTo(UItem* item, UInventoryComponent* to);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TransferAllItemsTo(UInventoryComponent* to);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SortItems();

	//Find item
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItem(UItem* item, int32& index);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<UItem*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Size = 20;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

		
};

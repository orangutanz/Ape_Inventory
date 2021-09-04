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
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem* item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItem* item);

	UFUNCTION(BlueprintCallable)
	void DeleteItem(UItem* item);

	UFUNCTION(BlueprintCallable)
	bool TransferItemTo(UItem* item, UInventoryComponent* to);

	UFUNCTION(BlueprintCallable)
	bool TransferAllItemsTo(UInventoryComponent* to);

	UFUNCTION(BlueprintCallable)
	void SortItems(){}

	//Find item
	UFUNCTION(BlueprintCallable)
	UItem* FindItem(UItem* item, int32& index);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<UItem*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Size = 20;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnRating = 1.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};

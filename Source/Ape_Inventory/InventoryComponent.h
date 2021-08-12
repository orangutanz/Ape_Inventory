// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APE_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	bool AddItem(class UItem* item);
	bool RemoveItem(class UItem* item);

	//Find item
	class UItem* FindItem(class UItem* item, int32& index);
	class UItem* FindItem_AfterIndex(class UItem* item, int32& index);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> Items;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Size;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};

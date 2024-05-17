// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "InventoryComponent.h"

UItem::UItem()
{

}

UItem::~UItem()
{
	Quantity = 0;
	OwnerInventory = nullptr;
}

void UItem::Use(AApe_InventoryCharacter* Character)
{
}

UItem* UItem::SplitItem(int32 num)
{
	if (MaxStack == 1 || num == 0)
	{
		return nullptr;
	}

	if (Quantity > num)
	{
		Quantity -= num;
		auto item = NewObject<UItem>();
		//auto item = CreateDefaultSubobject<UItem>(TEXT("SubClassItem")); also broken. problem might be somewhere else
		item->ItemID = ItemID;
		item->ItemType = ItemType;
		item->MaxStack = MaxStack;
		item->Quantity = num;

		return item;
	}
	else if (Quantity == num)
	{
		return this;
	}


	return nullptr;
}

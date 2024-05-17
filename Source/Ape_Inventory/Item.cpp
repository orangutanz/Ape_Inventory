// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "InventoryComponent.h"

UItem::UItem()
{

}

UItem::~UItem()
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

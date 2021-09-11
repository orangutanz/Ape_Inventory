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
	if (MaxStack == 1)
	{
		return nullptr;
	}

	if (Quantity > num)
	{
		Quantity -= num;
		auto item = NewObject<UItem>();
		item->ItemID = ItemID;
		item->Name = Name;
		item->Description = Description;
		item->ItemType = ItemType;
		item->Mesh = Mesh;
		item->Icon = Icon;
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

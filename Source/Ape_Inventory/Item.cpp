// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "InventoryComponent.h"

void UItem::SetItemInfo(FItemInfo info)
{
	mItemInfo = info;
}

bool UItem::SetQuantity(int32 num)
{
	if (num == 0 || num > mItemInfo.MaxStack)
		return false;

	mItemInfo.Quantity = num;
	return true;
}

UItem* UItem::SplitItem(int32 num)
{
	if (mItemInfo.MaxStack == 1 || num == 0)
	{
		return nullptr;
	}

	if (mItemInfo.Quantity > num)
	{
		FItemInfo newInfo = mItemInfo;
		newInfo.Quantity = num;
		mItemInfo.Quantity -= num;
		auto newItem = NewObject<UItem>();
		newItem->SetItemInfo(newInfo);

		return newItem;
	}
	else if (mItemInfo.Quantity == num)
	{
		return this;
	}


	return nullptr;
}

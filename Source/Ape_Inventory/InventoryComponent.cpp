#include "InventoryComponent.h"
#include "Item.h"
#include <cstdlib>

UInventoryComponent::UInventoryComponent()
{
	Items.Reserve(Size);
}

bool UInventoryComponent::AddItem(UItem* item)
{
	if (!item)
	{
		return false;
	}
	// if the item can not be stacked
	if (item->GetMaxStack() == 1)
	{
		if (Items.Num() >= Size)
		{
			return false;
		}
		else // add the item if there's a slot in the inventory
		{
			Items.Add(item);

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	int32 foundIndex = 0;
	UItem* itemFound = FindItem(item, foundIndex);

	// If there's no same item in the inventory for the item to be stacked
	if (!itemFound)
	{
		if (Items.Num() >= Size)
		{
			return false;
		}
		else // Add the item if there's a slot in the inventory
		{
			Items.Add(item);

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	else // If there're same items in the inventory already
	{
		while (itemFound && (item->GetQuantity() > 0))
		{
			int32 q = itemFound->GetQuantity();
			int32 m = itemFound->GetMaxStack();
			int32 p = item->GetQuantity();
			if (q == m) // If the item stack is full, find the next item.
			{
				itemFound = FindItem(item, ++foundIndex);
			}
			else if ((p + q) <= m) // If the item can be added within a stack
			{
				itemFound->SetQuantity(p + q);

				OnInventoryUpdated.Broadcast();
				return true;
			}
			else if ((p + q) > m) // If the item added will be more than max stack
			{
				itemFound->SetQuantity(m);
				item->SetQuantity(p - (m - q));
				itemFound = FindItem(item, ++foundIndex);
			}
		}
		//after all, still add the item if there's a space
		if ((item->GetQuantity() > 0) && (Items.Num() < Size))
		{
			Items.Add(item);

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	return false;
}

bool UInventoryComponent::RemoveItem(UItem* item)
{
	if (item)
	{
		Items.RemoveSingle(item);

		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

bool UInventoryComponent::SwapItemByIndex(const int32 a, const int32 b)
{
	if ((a >= 0 && a < Items.Num()) && (b >= 0 && b < Items.Num()) && (a != b))
	{
		Items.Swap(a, b);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}


bool UInventoryComponent::TransferItemTo(UItem* item, UInventoryComponent* to)
{
	if (item && to)
	{
		if (to->AddItem(item))
		{
			Items.RemoveSingle(item);
			return true;
		}
		OnInventoryUpdated.Broadcast();
	}
	return false;
}

bool UInventoryComponent::TransferAllItemsTo(UInventoryComponent* to)
{
	if (!to)
	{
		return false;
	}

	for (int i = Items.Num() - 1; i >= 0; --i)
	{
		to->AddItem(Items[i]);
	}

	OnInventoryUpdated.Broadcast();
	return false;
}

void UInventoryComponent::SortItems()
{	
	//ID sort
	//Items.Sort([](const UItem& a, const UItem& b) { return a.GetItemID().FastLess(b.GetItemID()); });

	//Type sort
	Items.Sort([](const UItem& a, const UItem& b) { return a.GetItemType() <= b.GetItemType(); });

	OnInventoryUpdated.Broadcast();
}


UItem* UInventoryComponent::FindItem(UItem* item, int32& index)
{
	if (item && (index < 0 || index >= Size))
	{
		return nullptr;
	}

	for (index; index <Items.Num(); index++)
	{
		if (item->GetItemID() == Items[index]->GetItemID())
		{
			return  Items[index];
		}
	}
	return nullptr;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


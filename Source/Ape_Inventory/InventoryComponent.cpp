#include "InventoryComponent.h"
#include "Item.h"
#include <cstdlib>

UInventoryComponent::UInventoryComponent()
{
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
		if (Items.Num() >= MaxSize)
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

	// Try find stackable items to add to
	//for (auto i : Items)
	//{
	//	if (i->GetItemID() == item->GetItemID())
	//	{
	//		int32 q = i->GetQuantity();
	//		int32 m = i->GetMaxStack();
	//		int32 p = item->GetQuantity(); 
	//		if (q == m) // If the item stack is full, find the next item.
	//		{
	//			continue;
	//		}
	//		else if ((p + q) <= m) // If the item can be added within the stackSize
	//		{
	//			i->SetQuantity(p + q);
	//
	//			OnInventoryUpdated.Broadcast();
	//			return true;
	//		}
	//		else if ((p + q) > m) // If the item added will be more than max stack
	//		{
	//			i->SetQuantity(m);
	//			item->SetQuantity(p - (m - q));
	//			itemFound = FindItem(item, ++foundIndex);
	//		}
	//	}
	//}

	int32 foundIndex = 0;
	
	UItem* itemFound = FindItemID(item->GetItemID(), foundIndex);

	// If there's no same item in the inventory for the item to be stacked
	if (!itemFound)
	{
		if (Items.Num() >= MaxSize)
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
				itemFound = FindItemID(item->GetItemID(), ++foundIndex);
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
				itemFound = FindItemID(item->GetItemID(), ++foundIndex);
			}
		}
		//after all, still add the item if there's a space
		if ((item->GetQuantity() > 0) && (Items.Num() < MaxSize))
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


void UInventoryComponent::SortItems(bool sortByItemID)
{	
	if (sortByItemID)
	{
		//ID sort
		Items.Sort([](const UItem& a, const UItem& b) { return a.GetItemID().FastLess(b.GetItemID()); });
	}
	else
	{
		//Type sort
		Items.Sort([](const UItem& a, const UItem& b) { return a.GetItemType() <= b.GetItemType(); });
	}

	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::TransferItems(UInventoryComponent* toInventory)
{
	if (!toInventory)
		return;

	TArray<UItem*> tempTransferedItems;
	for (auto i : Items)
	{
		if (toInventory->AddItem(i))
		{
			tempTransferedItems.Add(i);
		}
	}
	for(auto j : tempTransferedItems)
	{
		Items.RemoveSingleSwap(j);
	}

	OnInventoryUpdated.Broadcast();
}


UItem* UInventoryComponent::FindItemID(FName name, int32& index)
{
	if (name.IsNone() && (index < 0 || index >= MaxSize))
	{
		return nullptr;
	}

	for (index; index < Items.Num(); index++)
	{
		if (name == Items[index]->GetItemID())
		{
			return  Items[index];
		}
	}
	return nullptr;
}

bool UInventoryComponent::Contains(UItem* item, int& index)
{
	index = Items.Find(item);
	return (index >= 0);
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


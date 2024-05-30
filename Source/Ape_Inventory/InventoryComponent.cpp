#include "InventoryComponent.h"
#include "Item.h"
#include <cstdlib>

bool UInventoryComponent::AddItem(UItem* item)
{
	if (!item)
	{
		return false;
	}
	// Can item stacked
	if (item->GetMaxStack() == 1)
	{
		if (Items.Num() >= MaxSize)
		{
			return false;
		}
		else 
		{
			Items.Add(item);
			OnInventoryUpdated.Broadcast(); //Add new slot
			return true;
		}
	}

	int32 foundIndex = 0;
	
	UItem* itemFound = FindItemID(item->GetItemID(), foundIndex);

	// No item for stacking, try add to new slot
	if (!itemFound)
	{
		if (Items.Num() >= MaxSize)
		{
			return false; // No space
		}
		else
		{
			Items.Add(item);

			OnInventoryUpdated.Broadcast(); //Add new slot
			return true; // Fully added
		}
	}
	else // Found item for stacking
	{
		while (itemFound && (item->GetQuantity() > 0))
		{
			int32 q = itemFound->GetQuantity();
			int32 m = itemFound->GetMaxStack();
			int32 p = item->GetQuantity();
			if (q == m) // Found item is full, find the next item.
			{
				itemFound = FindItemID(item->GetItemID(), ++foundIndex);
			}
			else if ((p + q) <= m) // FoundItem can be fully stacked
			{
				itemFound->SetQuantity(p + q);

				itemFound->FOnItemUpdated.Broadcast();// update stacked item
				return true; // Fully added
			}
			else if ((p + q) > m) // Found item can be partially stacked
			{
				itemFound->SetQuantity(m);
				item->SetQuantity(p - (m - q));
				itemFound->FOnItemUpdated.Broadcast();// update stacked item
				itemFound = FindItemID(item->GetItemID(), ++foundIndex);
			}
		}
		//After stacking, try add the remaining to new slot
		if ((item->GetQuantity() > 0) && (Items.Num() < MaxSize))
		{
			Items.Add(item);

			OnInventoryUpdated.Broadcast();
			return true; // Fully added
		}
	}
	return false; // Only partially added
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

TArray<FItemInfo> UInventoryComponent::GetItemInfos()
{
	TArray<FItemInfo> outArr;
	for (auto i : Items)
	{
		outArr.Add(i->GetItemInfo());
	}
	return outArr;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


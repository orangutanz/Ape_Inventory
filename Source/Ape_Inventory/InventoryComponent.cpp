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
	if (item->MaxStack == 1)
	{
		if (Items.Num() >= Size)
		{
			return false;
		}
		else // add the item if there's a slot in the inventory
		{
			if (item->OwnerInventory)
			{
				item->OwnerInventory->RemoveItem(item);
			}
			Items.Add(item);
			item->OwnerInventory = this;

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
			if (item->OwnerInventory)
			{
				item->OwnerInventory->RemoveItem(item);
			}
			Items.Add(item);
			item->OwnerInventory = this;

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	else // If there're same items in the inventory already
	{
		while (itemFound && (item->Quantity > 0))
		{
			int32 q = itemFound->Quantity;
			int32 m = itemFound->MaxStack;
			int32 p = item->Quantity;
			if (q == m) // If the item stack is full, find the next item.
			{
				itemFound = FindItem(item, ++foundIndex);
			}
			else if ((p + q) <= m) // If the item can be added within a stack
			{
				itemFound->Quantity = p + q;
				if (item->OwnerInventory)
				{
					item->OwnerInventory->DeleteItem(item);
				}

				OnInventoryUpdated.Broadcast();
				return true;
			}
			else if ((p + q) > m) // If the item added will be more than max stack
			{
				itemFound->Quantity = m;
				item->Quantity = p - (m - q);
				itemFound = FindItem(item, ++foundIndex);
			}
		}
		//after all, still add the item if there's a space
		if ((item->Quantity > 0) && (Items.Num() < Size))
		{
			if (item->OwnerInventory)
			{
				item->OwnerInventory->RemoveItem(item);
			}
			Items.Add(item);
			item->OwnerInventory = this;

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

void UInventoryComponent::DeleteItem(UItem* item)
{
	if (item)
	{
		item->OwnerInventory = nullptr;
		Items.RemoveSingle(item);

		OnInventoryUpdated.Broadcast();
	}
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
		UInventoryComponent* originalOwner = item->OwnerInventory;
		if (to->AddItem(item))
		{
			originalOwner->Items.RemoveSingle(item);
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
	Items.Sort([](const UItem& a, const UItem& b) { return a.ItemID.FastLess(b.ItemID); });

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
		if (item->ItemID == Items[index]->ItemID)
		{
			return  Items[index];
		}
	}
	return nullptr;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnRating == 1.0f)
	{
		for (auto& item : DefaultItems)
		{
			AddItem(item);
		}
	}
	else
	{
		for (auto& item : DefaultItems)
		{
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if (r < SpawnRating)
			{
				AddItem(item);
			}
		}
	}

	OnInventoryUpdated.Broadcast();
}


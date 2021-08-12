#include "InventoryComponent.h"
#include "Item.h"



bool UInventoryComponent::AddItem(UItem* item)
{
	if (item)
	{
		return false;
	}
	// if the item can not be stacked
	if (item->maxStack == 1)
	{
		if (Items.Num() >= Size)
		{
			return false;
		}
		else // add the item if there's a slot in the inventory
		{
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
			Items.Add(item);
			item->OwnerInventory = this;

			OnInventoryUpdated.Broadcast();
			return true;
		}
	}
	else // If there're same items in the inventory already
	{
		while (item->Quantity > 0 && (foundIndex >= 0 && foundIndex < Size))
		{
			int32 q = itemFound->Quantity;
			int32 s = itemFound->maxStack;
			int32 p = item->Quantity;
			if (q == s) // If the item stack is full, find the next item.
			{
				itemFound = FindItem(item, ++foundIndex);
			}
			else if ((p + q) <= s) // If the item can be added within a stack
			{
				itemFound->Quantity = p + q;
				item->Quantity = 0;

				OnInventoryUpdated.Broadcast();
				return true;
			}
			else if ((p + q) > s) // If the item added will be more than max stack
			{
				itemFound->Quantity = p + q;
				item->Quantity = q - (s - p);

				itemFound = FindItem(item, ++foundIndex);
			}
			else if (Items.Num() < Size)
			{
				Items.Add(item);
				item->OwnerInventory = this;

				OnInventoryUpdated.Broadcast();
				return true;
			}
		}
	}
	return false;
}

bool UInventoryComponent::RemoveItem(UItem* item)
{
	if (item)
	{
		item->OwnerInventory = nullptr;
		Items.RemoveSingle(item);

		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

UItem* UInventoryComponent::FindItem(UItem* item, int32& index)
{
	if (item && (index < 0 || index >= Size))
	{
		return nullptr;
	}

	for (index; index <Items.Num(); index++)
	{
		if (item->itemID == Items[index]->itemID)
		{
			return  Items[index];
		}
	}
	return nullptr;
}



void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.Reserve(Size);

	for (auto& item : DefaultItems)
	{
		Items.Add(item);
	}

	OnInventoryUpdated.Broadcast();
}


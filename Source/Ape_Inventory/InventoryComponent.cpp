#include "InventoryComponent.h"
#include "Item.h"

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
	if (item->maxStack == 1)
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
			int32 m = itemFound->maxStack;
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

	for (auto& item : DefaultItems)
	{
		AddItem(item);
	}

	OnInventoryUpdated.Broadcast();
}


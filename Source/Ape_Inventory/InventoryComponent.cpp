#include "InventoryComponent.h"
#include "Item.h"

bool UInventoryComponent::AddItem(UItem* item)
{
	if (item)
	{
		return false;
	}
	int32 itemIndex = -1;
	UItem* itemFound = FindItem(item, itemIndex);

	//If there's no same item in the inventory
	if (!itemFound)
	{
		// Can not add item when inventory is full and there's no item to stack
		if (Items.Num() >= Size)
		{
			return false;
		}
		else
		{
			Items.Add(item);
		}
	}
	else
	{

	}

	return true;
}

bool UInventoryComponent::RemoveItem(UItem* item)
{
	return false;
}

UItem* UInventoryComponent::FindItem(UItem* item, int32& index)
{
	index = -1;
	if (item)
	{
		return nullptr;
	}

	for (int i = 0; i<Items.Num(); i++)
	{
		if (item->itemID == Items[i]->itemID)
		{
			index = i;
			return  Items[i];
		}
	}
	return nullptr;
}

UItem* UInventoryComponent::FindItem_AfterIndex(UItem* item, int32& index)
{
	if (item)
	{
		return nullptr;
	}

	index += 1;
	for (int i = index; i < Items.Num(); i++)
	{
		if (item->itemID == Items[i]->itemID)
		{
			index = i;
			return  Items[i];
		}
	}
	return nullptr;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


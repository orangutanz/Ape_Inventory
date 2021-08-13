#include "Item_Equipment.h"
#include "InventoryComponent.h"
#include "Ape_InventoryCharacter.h"

void UItem_Equipment::Use(class AApe_InventoryCharacter* character)
{
	if (character)
	{
		if (OwnerInventory)
		{
			if (curDurability > 0)
			{
				curDurability--;
				OwnerInventory->OnInventoryUpdated;
			}
			else
			{
				OwnerInventory->RemoveItem(this);
			}
		}
	}
}

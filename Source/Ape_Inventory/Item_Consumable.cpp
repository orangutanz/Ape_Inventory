#include "Item_Consumable.h"
#include "InventoryComponent.h"
#include "Ape_InventoryCharacter.h"

void UItem_Consumable::Use(AApe_InventoryCharacter* character)
{
	if (character)
	{
		if (Quantity > 0)
		{
			character->health += regenAmount;
			Quantity--;
		}
		if (OwnerInventory && Quantity == 0)
		{
			OwnerInventory->RemoveItem(this);
		}
	}
}

#include "Item_Consumable.h"
#include "InventoryComponent.h"
#include "Ape_InventoryCharacter.h"

void UItem_Consumable::Use(AApe_InventoryCharacter* character)
{
	if (character)
	{
		character->health += regenAmount;
		Quantity--;
		if (Quantity == 0)
		{
			OwnerInventory->RemoveItem(this);
		}
	}
}

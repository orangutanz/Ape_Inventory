// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "InventoryComponent.h"

UItem::UItem()
{

}

UItem::~UItem()
{
	Quantity = 0;
	OwnerInventory = nullptr;
}

void UItem::Use(AApe_InventoryCharacter* Character)
{
}

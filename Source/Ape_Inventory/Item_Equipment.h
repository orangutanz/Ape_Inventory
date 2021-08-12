// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Equipment.generated.h"

/**
 * 
 */
UCLASS()
class APE_INVENTORY_API UItem_Equipment : public UItem
{
	GENERATED_BODY()

protected:
	virtual void Use(class AApe_InventoryCharacter* character) override;
	
};

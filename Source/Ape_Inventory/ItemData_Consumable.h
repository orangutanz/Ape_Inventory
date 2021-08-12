// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item_Consumable.h"
#include "ItemData_Consumable.generated.h"

UCLASS(BlueprintType)
class APE_INVENTORY_API UItemData_Consumable : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<FConsumableInfo> ConsumableDatabase;

};

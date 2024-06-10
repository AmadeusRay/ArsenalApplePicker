// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dumm.generated.h"

/**
 * 
 */
UCLASS(BLueprintable, BlueprintType)
class ARSENALAPPLEPICKER_API UDumm : public UObject
{
	GENERATED_BODY()
public:
	UDumm();


	UPROPERTY(BlueprintReadWrite)
		uint8 Health;

	UFUNCTION(BlueprintCallable)
		void Hello();
};

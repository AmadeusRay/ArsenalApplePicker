// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ApplePickerWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class ARSENALAPPLEPICKER_API UApplePickerWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetAppleCollectedText(int32 ApplesCollected, int32 ApplesToCollect);

	UFUNCTION(BlueprintImplementableEvent)
	void SetGameOverText(bool bWonGame);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float GameStartDelay{ 5.0f };


};
